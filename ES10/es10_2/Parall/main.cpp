#include "main.h"
#include "random.h"
#include "population.h"
#include "mpi.h"


int main (int argc, char* argv[]){

	//Inizializzo MPI.
	int size, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status stat[24];
	double tstart= MPI_Wtime();

	int itag[24];
	for(int i=0;i<24;++i){
		itag[i]=i+1;
	}


	rnd = SetRandom(rnd, rank); //setto il generatore di numeri Random doverso per ogni processore
	rndGlobal= SetRandom(rndGlobal,5); //setto un random comune ad ogni processore
	
	// cities = CityVectorCirc();
	// cities = CityVectorSquare(); //creo il vettore delle 32 citta
	ReadCityVector("citta.0");
	
	Population s = FirstPopulation(n_Ind,cities); //Prima popolazione solo con permutazione a coppie n_Ind è la dimensione della popolazione e cities è il vettore delle citta
	

	
	for(int f=0;f<n_gen;++f){
		if (f%100==0) cout<<"Generazione numero: "<<f<<" processore numero: "<<rank<<endl;
		//Pulisco il vettore degli individui utilizzato per la popolazione precedente
		VecInd.clear();
		for(int i=0;i<n_Ind*0.5;++i){
			//Seleziono due individui
			One=s.SelectInd(p);
			Two=s.SelectInd(p);
			//controllo che siano diversi
			control=0;
			while(control<1){
				if(One==Two) Two=s.SelectInd(p);
				else control++;
			}
			
			pair <Individual,Individual> Sons (s.Pop[One],s.Pop[Two]); //Creo la coppia di figli che inizializzo a genitori

			//Due numeri Random per le probabilità di mutazione e crossover
			double uCross=rnd.Rannyu();
			double uMut=rnd.Rannyu();

			// Effettuo il cross over con una probabilita p 60%
			if(uCross<0.6) Sons = s.CrossOver(One,Two);
			
			else Sons = s.NoCrossOver(One,Two);

			// Faccio le mutazioni tutte con probabilità 8%
			if(uMut<0.08){
				Sons.first.P1();
				Sons.second.P1();
			}	
			else if(uMut>=0.08 && uMut<0.16){
				Sons.first.P2();
				Sons.second.P2();
			}
			else if(uMut>=0.16 && uMut<0.24){
				Sons.first.P3();
				Sons.second.P3();
			}
			else if(uMut>=0.24 && uMut<0.32){
				Sons.first.P4();
				Sons.second.P4();
			}		
			

			//Metto i figli nel vettore individui per la nuova popolazione
			VecInd.push_back(Sons.first);
			VecInd.push_back(Sons.second);
		}

		s=Population(VecInd); //Creo la nuova popolazione
		
		/*Qui faccio comunicare i continenti in modo randomico ogni tot generazioni.
		Si scambiano la prima metà della popolazione (la metà buona) e poi continuano.
		Alla fine cerchero il miglior percorso tra i continenti.*/
		if(f%n_migr== 0){
			int Cont1 = rndGlobal.Rannyu()*size;
			int Cont2 = rndGlobal.Rannyu()*size;
			int Cont3 = rndGlobal.Rannyu()*size;
			int Cont4 = rndGlobal.Rannyu()*size;
			
			//controllo che i continenti siano diversi
			bool comm = false;
			while(comm == false){
				if(Cont1!=Cont2) comm = true;
				else Cont2 = rndGlobal.Rannyu()*size;
			}

			comm = false;
			while(comm == false){
				if(Cont3!=Cont2 && Cont3!=Cont1) comm = true;
				else Cont3=rndGlobal.Rannyu()*size;
			}

			comm = false;
			while(comm == false){
				if(Cont4!=Cont2 && Cont4!=Cont1 && Cont4!=Cont3) comm = true;
				else Cont4=rndGlobal.Rannyu()*size;
			}

			//QUI scambio tutte le quantità in modo molto brutto ma efficace
			for(int i=0;i<s.Pop.size()*0.5;++i){

				for(int j=0;j<s.Pop[i].Path.size();++j){

					if(rank == Cont1){
						MPI_Send(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont2,itag[0],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont2,itag[6],MPI_COMM_WORLD,&stat[6]);
					}
					else if(rank == Cont2){
						MPI_Recv(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont1,itag[0],MPI_COMM_WORLD,&stat[0]);
						MPI_Send(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont1,itag[6],MPI_COMM_WORLD);	
					}
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont4,itag[12],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont4,itag[18],MPI_COMM_WORLD,&stat[18]);
					}
					else {
						MPI_Recv(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont3,itag[12],MPI_COMM_WORLD,&stat[12]);
						MPI_Send(&s.Pop[i].Path[j][0],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont3,itag[18],MPI_COMM_WORLD);
					}
				}
			}

			for(int i=0;i<s.Pop.size()*0.5;++i){
				for(int j=0;j<s.Pop[i].Path.size();++j){
					if(rank == Cont1){
						MPI_Send(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont2,itag[1],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont2,itag[7],MPI_COMM_WORLD,&stat[7]);
					}
					else if(rank == Cont2){
						MPI_Send(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont1,itag[7],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont1,itag[1],MPI_COMM_WORLD,&stat[1]);
					}
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont4,itag[13],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont4,itag[19],MPI_COMM_WORLD,&stat[19]);
					}
					else {
						MPI_Recv(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont3,itag[13],MPI_COMM_WORLD,&stat[13]);
						MPI_Send(&s.Pop[i].Path[j][1],s.Pop[i].Path[0].size(),MPI_DOUBLE,Cont3,itag[19],MPI_COMM_WORLD);
					}
				}
			}

			for(int i=0;i<s.Pop.size()*0.5;++i){
				for(int j=0;j<s.Pop[i].Path.size();++j){
					if(rank == Cont1){
						MPI_Send(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont2,itag[2],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont2,itag[8],MPI_COMM_WORLD,&stat[8]);
					}
					else if(rank == Cont2){
						MPI_Recv(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont1,itag[2],MPI_COMM_WORLD,&stat[2]);
						MPI_Send(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont1,itag[8],MPI_COMM_WORLD);
					}
				
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont4,itag[14],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont4,itag[20],MPI_COMM_WORLD,&stat[20]);
					}
					else {
						MPI_Recv(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont3,itag[14],MPI_COMM_WORLD,&stat[14]);
						MPI_Send(&s.Pop[i].Path[j][2],s.Pop[i].Path[0].size(),MPI_INTEGER,Cont3,itag[20],MPI_COMM_WORLD);
					}
				}
			}

			for(int i=0;i<s.Pop.size()*0.5;++i){
				for(int j=0;j<s.Pop[i].Path.size();++j){
					if(rank == Cont1){
						MPI_Send(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont2,itag[3],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont2,itag[9],MPI_COMM_WORLD,&stat[9]);
					}
					else if(rank == Cont2){
						MPI_Recv(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont1,itag[3],MPI_COMM_WORLD,&stat[3]);
						MPI_Send(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont1,itag[9],MPI_COMM_WORLD);
					}
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont4,itag[15],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont4,itag[21],MPI_COMM_WORLD,&stat[21]);
					}
					else {
						MPI_Recv(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont3,itag[15],MPI_COMM_WORLD,&stat[15]);
						MPI_Send(&s.Pop[i].Fitness,1,MPI_DOUBLE,Cont3,itag[21],MPI_COMM_WORLD);
					}
				}
			}

			for(int i=0;i<s.Pop.size()*0.5;++i){
				for(int j=0;j<s.Pop[i].Path.size();++j){
					if(rank == Cont1){
						MPI_Send(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont2,itag[4],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont2,itag[10],MPI_COMM_WORLD,&stat[10]);
					}
					else if(rank == Cont2){
						MPI_Recv(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont1,itag[4],MPI_COMM_WORLD,&stat[4]);
						MPI_Send(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont1,itag[10],MPI_COMM_WORLD);
					}
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont4,itag[16],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont4,itag[22],MPI_COMM_WORLD,&stat[22]);
					}
					else {
						MPI_Recv(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont3,itag[16],MPI_COMM_WORLD,&stat[16]);
						MPI_Send(&s.Pop[i].PathLength,1,MPI_DOUBLE,Cont3,itag[22],MPI_COMM_WORLD);
					}
				}
			}

			for(int i=0;i<s.Pop.size()*0.5;++i){
				for(int j=0;j<s.Pop[i].Path.size();++j){
					if(rank == Cont1){
						MPI_Send(&s.Pop[i].Check,1,MPI_C_BOOL,Cont2,itag[5],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Check,1,MPI_C_BOOL,Cont2,itag[11],MPI_COMM_WORLD,&stat[11]);				
					}
					else if(rank == Cont2){
						MPI_Recv(&s.Pop[i].Check,1,MPI_C_BOOL,Cont1,itag[5],MPI_COMM_WORLD,&stat[5]);				
						MPI_Send(&s.Pop[i].Check,1,MPI_C_BOOL,Cont1,itag[11],MPI_COMM_WORLD);
					}
					else if(rank == Cont3){
						MPI_Send(&s.Pop[i].Check,1,MPI_C_BOOL,Cont4,itag[17],MPI_COMM_WORLD);
						MPI_Recv(&s.Pop[i].Check,1,MPI_C_BOOL,Cont4,itag[23],MPI_COMM_WORLD,&stat[23]);
					}
					else {
						MPI_Recv(&s.Pop[i].Check,1,MPI_C_BOOL,Cont3,itag[17],MPI_COMM_WORLD,&stat[17]);				
						MPI_Send(&s.Pop[i].Check,1,MPI_C_BOOL,Cont3,itag[23],MPI_COMM_WORLD);
					}
				}
			

			}
		}
	}

	//Ho la popolazione finale qua una per ogni processore qual è la migliore?
	
	
	if(rank==0){
		pro1.open("pro1.0");
		for (int i=0;i<s.Pop.size();++i){
			pro1<<s.Pop[i].PathLength<<" ";
			for(int j=0;j<s.Pop[i].Path.size();++j){
				pro1<<s.Pop[i].Path[j][2]<<" ";
			}
			pro1<<endl;
		}
		pro1.close();

		// BestPath.open("/Users/nicolabrancadori/Documents/SimulazioneNumerica/lezione10/ES10_2/Esercizio/BestPathParall.0");
		// for(int i=0; i<s.Pop[0].Path.size();++i){
		// 	BestPath<<s.Pop[0].Path[i][0]<<" "<<s.Pop[0].Path[i][1]<<" "<<s.Pop[0].Path[i][2]<<endl;
		// }
		// BestPath.close();
	}
	
	else if(rank==1){
		pro2.open("pro2.0");
		for (int i=0;i<s.Pop.size();++i){
			pro2<<s.Pop[i].PathLength<<" ";
			for(int j=0;j<s.Pop[i].Path.size();++j){
				pro2<<s.Pop[i].Path[j][2]<<" ";
			}
			pro2<<endl;
		}
		pro2.close();
	}
	
	else if(rank==2){
		pro3.open("pro3.0");
		for (int i=0;i<s.Pop.size();++i){
			pro3<<s.Pop[i].PathLength<<" ";
			for(int j=0;j<s.Pop[i].Path.size();++j){
				pro3<<s.Pop[i].Path[j][2]<<" ";
			}
			pro3<<endl;
		}
		pro3.close();
		
		// BestPath.open("../BestPathParall.0");
		// for(int i=0; i<s.Pop[0].Path.size();++i){
		// 	BestPath<<s.Pop[0].Path[i][0]<<" "<<s.Pop[0].Path[i][1]<<" "<<s.Pop[0].Path[i][2]<<endl;
		// }
		// BestPath.close();
	}
	
	else{
		pro4.open("pro4.0");
		for (int i=0;i<s.Pop.size();++i){
			pro4<<s.Pop[i].PathLength<<" ";
			for(int j=0;j<s.Pop[i].Path.size();++j){
				pro4<<s.Pop[i].Path[j][2]<<" ";
			}
			pro4<<endl;
		}
		pro4.close();
	}
	

	double tend= MPI_Wtime();
	double dt= tend - tstart;

	cout<<"Sono: "<<rank<< " tempo: "<<dt<<endl;
		
	MPI_Finalize();
	
	return 0;
}

	
Random SetRandom(Random e, int a){
	int p1, p2,p3,p4,p5,p6,p7,p8;
	int seed[4];
	
	ifstream Primes("Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8;
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("seed.in");
	string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				if(a==0) e.SetRandom(seed,p1,p2);
				else if(a==1) e.SetRandom(seed,p3,p4);
				else if(a==2) e.SetRandom(seed,p5,p6);
				else if(a==3) e.SetRandom(seed,p7,p8);
				else e.SetRandom(seed,p1,p2);
			}
		}
		input.close();
	} else cerr << "PROBLEM: Unable to open seed.in" << endl;

	return e;
}

vector <vector <double> > CityVectorCirc(void){

	vector< vector<double> > c; //matrice delle città
	for (int i=0;i<n_cities;++i){
		vector <double> row;
		double theta=2*M_PI*rnd.Rannyu();
		
		row.push_back(cos(theta));
		row.push_back(sin(theta));
		row.push_back(i+1);

		c.push_back(row);	
	}
	
	return c;
}

vector <vector <double> > CityVectorSquare(void){

	vector< vector<double> > c; //matrice delle città
	for (int i=0;i<n_cities;++i){
		vector <double> row;
		
		row.push_back(2.*rnd.Rannyu()-1.);
		row.push_back(2.*rnd.Rannyu()-1.);
		row.push_back(i+1);

		c.push_back(row);	
	}
	
	return c;
}


void ReadCityVector(string a){
	ifstream in(a);
	vector<double> v;
	double x,y,n;
	while(!in.eof()){
		in>>x>>y>>n;
		
		v.push_back(x);
		v.push_back(y);
		v.push_back(n);
		
		cities.push_back(v);
		
		v.clear();
	}
	return;
}

Population FirstPopulation(int n_ind, vector <vector <double> > citta){
	vector <Individual> v;
	for(int i=0;i<n_Ind;++i){
		vector <vector <double> > cit = citta;
		int c=0;
		int k=(int) cit.size()*rnd.Rannyu();
		int l=(int) cit.size()*rnd.Rannyu();
		while(c<1){
			if(k!=l && l!=0 && k!=0){
				swap(cit[l][0],cit[k][0]);
				swap(cit[l][1],cit[k][1]);
				swap(cit[l][2],cit[k][2]);
				c++;
			}
			else{
				k=(int) cit.size()*rnd.Rannyu();
				l=(int) cit.size()*rnd.Rannyu();				
			}
		}
		Individual ind(cit);
		v.push_back(ind);
	}
	Population s(v);

	return s;
}
