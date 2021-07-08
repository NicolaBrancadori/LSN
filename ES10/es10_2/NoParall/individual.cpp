#include <iostream>
#include <fstream>
#include "individual.h"
#include "random.h"




Individual::Individual(vector< vector<double> > cit){
	
	Path=cit;
	Path.push_back(cit[0]);

	CalPathLength();
	CalCheck();
	Fitness=0.0;

	SetRandom();
}

void Individual::UpdateInd(){
	
	CalPathLength();
	CalCheck();
	Fitness=0.0;	
	
	return;
}

void Individual::SetRandom(void){
	Random rnd;
	int seed[4];
	int p1,p2;
	
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

	R=rnd;
	return;
}

void Individual::CalPathLength(void){
	double sum=0;
	
	for(int i=0; i<Path.size()-1;++i){
		sum+= sqrt(pow(Path[i][0]-Path[i+1][0],2)+pow(Path[i][1]-Path[i+1][1],2));
	}
	
	PathLength=sum;
	return ;
}

void Individual::CalCheck(){
	int l=0;
	for (int i=0;i<Path.size()-1;++i){
		for (int j=i+1;j<Path.size()-1;++j){
			if(Path[i][2]==Path[j][2]){
				l++;
			}
		}
	}
	if(Path[0][2]!=1 || Path[Path.size()-1][2]!=1) l++;

	if(l==0) Check=true;
	else Check=false; 
	
	return;
}

void Individual::P1(void){
	int c=0;
	int CityOne=R.Rannyu()*(Path.size()-3)+1; //citta casuale uno
	int CityTwo=R.Rannyu()*(Path.size()-3)+1; //citta casuale due
	
	while(c<1){
		if(CityOne!=CityTwo && CityOne!=0 && CityTwo!=0){
			swap( Path[CityOne], Path[CityTwo]);
			c++;
		}
		else{
			CityOne=R.Rannyu()*(Path.size()-3)+1;
			CityTwo=R.Rannyu()*(Path.size()-3)+1;
		}
		
	}

	UpdateInd();

	return;
}

void Individual::P2(void){

	int n_city=R.Rannyu()*(Path.size()-4)+1; //numero di citta da traslare
	int city=R.Rannyu()*(Path.size()-2-n_city)+1; //citta di partenza	
	
	int shift=R.Rannyu()*(Path.size()-2-n_city-city)+1; //shift spostamento +n
	
	int times=0;
	while(times<shift){
		for(int i=n_city-1;i>=0;--i) swap(Path[city+times+i], Path[city+times+i+1]);
		times++;
	}

	UpdateInd();
	
	return;
}


void Individual::P3(void){

	int mCities=R.Rannyu()*((int)(Path.size()-2)*0.5-1)+1; //m citta

	int c_one=0;
	int CityOne=R.Rannyu()*(Path.size()-2-mCities)+1.5;//Possibili citta di partenza delle prime m citta 
	
	while(c_one<1){
		if(CityOne-1 < mCities && Path.size()-2-(CityOne+mCities-1) < mCities){
			CityOne=R.Rannyu()*(Path.size()-2-mCities)+1.5;
		}
		else c_one++;
	}

	int c_two=0;
	int CityTwo=R.Rannyu()*(Path.size()-2-mCities)+1.5;//Possibili citta di partenza delle seconde m citta 
	
	while(c_two<1){
		if(abs(CityOne - CityTwo) < mCities && CityTwo+mCities-1 < CityTwo){
			CityTwo=R.Rannyu()*(Path.size()-2)+1.5;
		}
		else c_two++;
	}
	

	for(int i=0;i<mCities;++i){	
		swap(Path[CityOne + i],Path[CityTwo + i]);
	}

	UpdateInd();

	return;



}

void Individual::P4(void){
	
	int mCities=R.Rannyu()*(Path.size()-3)+1; //numeri di citta possibili
	int CityOne=R.Rannyu()*(Path.size()-2-mCities)+1; //Punti di partenza possibili

	for(int i=0; i<(int)(mCities*0.5);++i){
		swap(Path[CityOne+i],Path[CityOne+mCities-1-i]);
	}
	
	UpdateInd();

	return;

}

