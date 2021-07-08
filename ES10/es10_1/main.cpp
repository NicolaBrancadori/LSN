#include "main.h"
#include "random.h"
#include "individual.h"



int main (){

	//setto il generatore di numeri Random.
	SetRandom();
	
	//creo il vettore delle 32 citta.
	//cities = CityVectorSquare();
	cities = CityVectorCirc();

	//Creo il primo individuo uguale al vettore delle città.
	Individual Ind(cities);
	Individual BestInd = Ind; //è il mio individuo migliore per ora.
	


	
	int c=1;
	while(Temp>0.2){
		accepted=0;
		proposed=0;
		for(int i=0;i<nsteps;++i){

			if((i+1) % 1000000 == 0) cout<<"passi fatti: "<<(i+1)/1000000<<" milioni"<<endl;	
			
			//Permuto l'individuo: propongo una mossa
			Individual NewInd = CallPerm(Ind);
			proposed++;
		
			//Definisco la proabilità di accettazione
			if(NewInd.PathLength > Ind.PathLength){
				p=BoltzWeight(Ind ,NewInd );
				if(rnd.Rannyu() < p){ //Se il numero random che genero è minore della probabilità di accettazione allora accetta
					Ind = NewInd;
					accepted++;
				}
			}


			else{
				Ind = NewInd;
				accepted++;
				// cout<<"ACCETTATO NO METR"<<endl;
				// sum+=1.;
				if(Ind.PathLength < BestInd.PathLength) BestInd = Ind;
			}
		}
		//Stampo a file la lunghezza del miglio percorso.
		out_BestInd.open("MigliorIndividuo.0",ios::app);
		out_BestInd<<BestInd.PathLength<<endl;
		out_BestInd.close();
		
		cout<<"ciclo n: "<<c<<endl;
		cout<<"Passi: "<<nsteps<<endl;
		cout<<"T: "<<Temp<<endl;
		cout<<"Accettanza: "<<setprecision(15)<<accepted/(double)proposed<<endl;
		
		Temp*=0.90;
		beta=1/Temp;
		c++;
	}

	//Stampo a file il percorso migliore
	out_BestPath.open("MigliorPercorso.dat");
	for(int i=0;i<BestInd.Path.size();++i){
		out_BestPath<<BestInd.Path[i][0]<<" "<<BestInd.Path[i][1]<<" "<<BestInd.Path[i][2]<<endl;
	}
	out_BestPath.close();

	//TEMPERATURA INIZIALE
	/*
	ofstream outTemp("Temperatura.0");
	vector <double> T;
	vector <double> DeltaL;
	p=0.99;
	while(p>0.79){
		cout<<"Sto facendo con p="<<p<<endl;
		for(int i=0; i<nsteps;++i){
			if ( (i+1) % 100000 == 0) cout<<i+1<<endl;

			Individual NewInd = CallPerm(Ind);

			if(NewInd.PathLength > Ind.PathLength){
				if(rnd.Rannyu() < p){
					DL = NewInd.PathLength - Ind.PathLength;
					Temp = - DL / log(p);
					DeltaL.push_back(DL);
					T.push_back(Temp);

					// outTemp<<Temp<<" "<<NewInd.PathLength - Ind.PathLength<<endl;
					Ind = NewInd;

				}

			}
			else{
				Ind = NewInd;
			}
		}
	outTemp<<*max_element(T.begin(),T.end())<<" "<<*max_element(DeltaL.begin(),DeltaL.end())<<" "<<p<<endl;
	DeltaL.clear();
	T.clear();
	p-=0.01;
	}
	outTemp.close();
	*/




	return 0;
}


void SetRandom(void){
	
	ifstream Primes("Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else cerr << "PROBLEM: Unable to open Primes" << endl;
	Primes.close();

	ifstream input("seed.in");
	string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				rnd.SetRandom(seed,p1,p2);
			}
		}
		input.close();
	} else cerr << "PROBLEM: Unable to open seed.in" << endl;

	return;
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

Individual CallPerm(Individual ind){
	double p=rnd.Rannyu();

	if(p<0.25){
		ind.P1();
	}	
	else if(p>=0.25 && p<0.5){
		ind.P2();
	}
	else if(p>=0.5 && p<0.75){
		ind.P3();
	}
	else if(p>=0.75 && p<1.0){
		ind.P4();
	}		
	
	return ind;
}

double BoltzWeight(Individual ind,Individual newind){
	return exp(-beta*(newind.PathLength - ind.PathLength));
}





