
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

double error(double *AV,double *AV2,int n){
	if (n==0) return 0;
	else {
		return sqrt((AV2[n]-pow(AV[n],2))/n);
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

  
	//ESERCIZIO 1.1
	int M=10000;
	int N=100;
	double I[100]={0};
	double I2[100]={0};
	double sum_prog[100]={0};
	double sum2_prog[100]={0};
	double err_prog[100]={0};
	int k=0;
	while(k<N){
		double sum=0;
		for(int i=0;i<M/N;i++){
			sum+=cos(M_PI*rnd.Rannyu()*0.5); //la x sulla quale valuto la funzione è generata uniformemente in (0,1)
		}
	I[k]=1.*M_PI*0.5/(M/N)*sum; //ottengo 100 valori dell'integrale, ho fatto la media a blocchi con 10000 step e 100 blocchi.
	I2[k]=pow(I[k],2);
	k++;
	}

	k=0;
	ofstream Res_int;
	Res_int.open("risultati_int.dat");
	if (Res_int.is_open()){
		while(k<N){
			for(int i=0;i<k+1;i++){
				sum_prog[k]+=I[i];
				sum2_prog[k]+=I2[i];
			}
		sum_prog[k]/=(k+1); //media progressiva all'aumentare del numero di blocchi.
		sum2_prog[k]/=(k+1);
		err_prog[k]=error(sum_prog,sum2_prog,k); //errore progressivo all'aumentare del numero di blocchi.
		Res_int<<sum_prog[k]<<" "<<err_prog[k]<<endl;
		k++;
		}
	}
	else {cerr<<"Problem: unable to open risultati_int.dat"<<endl;}
	Res_int.close();


//ESERCIZIO 1.2
	//Per ottenere p(x) ho sviluppato il coseno fino al quarto ordine;
	for(int i=0;i<100;i++){
		err_prog[i]=0;
		I[i]=0;
		I2[i]=0;
		sum_prog[i]=0;
		sum2_prog[i]=0;
	}

	for(int j=0;j<N;j++){
		k=0;
		double sum=0;
		while(k<M/N){//dentro faccio un rejection sampling per campionare le variabili secondo p(x).
			double p_max=M_PI/2.;
			double x=rnd.Rannyu();
			double r=p_max*rnd.Rannyu();
			double p_x=(1-pow(M_PI*x,2)/8.+pow(x*M_PI,4)/384.)/(1-pow(M_PI,2)/24.+pow(M_PI,4)/1920.);
			if (r<p_x) {
				sum+=M_PI*0.5*cos(M_PI*x*0.5)*(1/p_x); 
				k++;
			}
			else continue;
		}
		I[j]=sum/float(M/N); //ottengo 100 valori dell'integrale, ho fatto la media a blocchi.
		I2[j]=pow(I[j],2);
	}

	k=0;
	ofstream Res_int_px;
	Res_int_px.open("risultati_int_px.dat");
	if (Res_int_px.is_open()){
		while(k<N){
			for(int j=0;j<k+1;j++){
				sum_prog[k]+=I[j];
				sum2_prog[k]+=I2[j];
			}
		sum_prog[k]/=(k+1); //media progressiva all'aumentare del numero di blocchi.
		sum2_prog[k]/=(k+1);
		err_prog[k]=error(sum_prog,sum2_prog,k); //errore progressivo all'aumentare del numero di blocchi.
		Res_int_px<<sum_prog[k]<<" "<<err_prog[k]<<endl;
		k++;
		}
	}
	else{ cerr<<"Problem: Unable to open risultati_int_px.dat"<<endl;}
	Res_int_px.close();
	

	return 0;
}

