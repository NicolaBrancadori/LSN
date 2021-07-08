#include "main.h"
#include "random.h"
#include "population.h"


int main (){

	SetRandom(); //setto il generatore di numeri Random
	
	// cities = CityVectorCirc(); //creo il vettore delle 32 citta
	// cities = CityVectorSquare();
	ReadCityVector("citta.0");
	
	Population s = FirstPopulation(n_Ind,cities); //Prima popolazione solo con permutazione a coppie n_Ind è la dimensione della popolazione e cities è il vettore delle citta
	

	
	
	// Effettuo il cross over con una probabilita p 60%
	for(int f=0;f<n_gen;++f){
		if (f%10==0) cout<<"Generazione numero: "<<f<<endl;
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

			//Cross over
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
	}

	
	//Stampo il miglior percorso (le coordinate anche non solo il vettore di interi)
	BestPath.open("../BestPathNoParall.0");
	for (int i = 0; i < s.Pop[0].Path.size(); ++i){
		BestPath<<s.Pop[0].Path[i][0]<<" "<<s.Pop[0].Path[i][1]<<" "<<s.Pop[0].Path[i][2]<<endl;
	}
	BestPath.close();



	// Questo che seguo l'ho utilizzato per l'istogramma di p (Per l'algoritmo di selezione).
	// int indice;
	// ofstream Index("Indici.0");
	// for(int i=0;i<1000000;++i){
	// 	indice=s.SelectInd(p);
	// 	Index<<indice<<endl;
	// }
	// Index.close();
	
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
