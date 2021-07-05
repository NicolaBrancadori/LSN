#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

float error(float * AV,float * AV2,int n){
	if (n==0) return 0;
	else{
		return sqrt((AV2[n]-AV[n]*AV[n])/n);
  	}
}


int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
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
   	
   	/*
	//INIZIO ESERCIZIO
	//Esercizio risolto utilizzando il valore di pigreco
	int M=100000;
	int l=100;
	int N=100;
	float pi[100]={0};
	float pi2[100]={0};
	float sum_prog[100]={0};
	float sum2_prog[100]={0};
	float err_prog[100]={0};
	
	//Divido i miei 10mila steps in 100 blocchi da 100 steps e ottengo quindi 100 stime di pigreco
	for(int k=0;k<N;k++){
		int counts=0;
		for(int i=0;i<M/N;i++){
			double r=rnd.Rannyu();
			double theta= 2*M_PI*rnd.Rannyu();
			for(int j=0;j<l;j++){
				if(0.008*cos(theta)+r>r && 0.008*cos(theta)+r>(j/100.) && r<(j/100.)) counts++;
				if(0.008*cos(theta)+r<r && 0.008*cos(theta)+r<(j/100.) && r>(j/100.)) counts++;
			}
		}
		pi[k]=2*0.008*(M/N)/(counts/float(l)); //queste sono le 100 stime di pi greco.
		pi2[k]=pow(pi[k],2); //qui metto i quadrati per la valutazione del'errore che faccio dopo.
	}

	//Qui faccio al crescere del numero di blocchi N le medie del pigreco di ogni blocco e l'errore della media.
	//Questo per vedere come variano quest ultimi all'aumentare del numero di blocchi e quindi degli steps.
	ofstream pi_greco;
	pi_greco.open("risultati.dat");
	if(pi_greco.is_open()){
		int p=0;
		while(p<N){
			for(int i=0;i<p+1;i++){
				sum_prog[p]+=pi[i];
				sum2_prog[p]+=pi2[i];
			}
		sum_prog[p]/=float(p+1);
		sum2_prog[p]/=float(p+1);
		err_prog[p]= error(sum_prog,sum2_prog,p);
		pi_greco<<sum_prog[p]<<" "<<err_prog[p]<<endl;
		p++;
		}
	} else cerr<<"impossibile aprire risultati.dat"<<endl;
	pi_greco.close();
	*/


//ESERCIZIO risolto usando il rejecting sample ma comunque uso pigreco.

	int M=10000;
	int l=100;
	int N=100;
	float pi[1000]={0};
	float pi2[1000]={0};
	float sum_prog[1000]={0};
	float sum2_prog[1000]={0};
	float err_prog[1000]={0};	
	for(int k=0;k<N;k++){
		int counts=0;
		for(int i=0;i<M/N;i++){
	   		double r=rnd.Rannyu();
			int cycle=0;
			double Theta=0.;
			while(cycle==0){
				double x=2.*rnd.Rannyu()-1.;
				double y=2.*rnd.Rannyu()-1.;
				if((pow(x,2)+pow(y,2))<1.){ 
					if(y>0) Theta=atan(y/x);
					else Theta=2*M_PI-atan(y/x);
					cycle++;	
				}
				else continue;
			}
			for(int j=0;j<l;j++){
				if(0.0095*cos(Theta)+r>r && 0.0095*cos(Theta)+r>(j/float(l)) && r<(j/float(l))) counts++;
				if(0.0095*cos(Theta)+r<r && 0.0095*cos(Theta)+r<(j/float(l)) && r>(j/float(l))) counts++;
			}
		}
		pi[k]=2*0.0095*(M/N)/(counts/float(l));
		// cout<<pi[k]<<endl;
		pi2[k]=pow(pi[k],2);	
	}
	

	ofstream pi_greco;
	pi_greco.open("risultati.dat");
	if(pi_greco.is_open()){
		int p=0;
		while(p<N){
			for(int i=0;i<p+1;i++){
				sum_prog[p]+=pi[i];
				sum2_prog[p]+=pi2[i];
			}
		sum_prog[p]/=float(p+1);
		sum2_prog[p]/=float(p+1);
		err_prog[p]= error(sum_prog,sum2_prog,p);
		pi_greco<<sum_prog[p]<<" "<<err_prog[p]<<endl;
		p++;
		}
	} else cerr<<"impossibile aprire risultati.dat"<<endl;
	pi_greco.close();



	return 0;
}
