
#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include <cmath>

double error(double *AV, double *AV2, int n ){
  if(n==0) return 0;
  else{
     return sqrt((AV2[n]-pow(AV[n],2))/n);
  }
}


using namespace std;
 
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
  
  //CALL DIRETTO
  //Parametri
  int M=1000000;
  int N=100;
  double r=0.1;
  double Sg=0.25;
  double T=1.;
  double K=100.;
  
  //Variabili per Data blocking
  double ave[M/N];
  double ave2[M/N];
  double sum_prog[M/N];
  double sum2_prog[M/N];
  double err_prog[M/N];

  //inizializzo i vettori
  for(int i=0;i<M/N;i++){
    ave[i]=0;
    ave2[i]=0;
    sum_prog[i]=0;
    sum2_prog[i]=0;
    err_prog[i]=0;    
  }

  int k=0;
  while(k<N){
    double sum=0.;
    for(int i=0;i<M/N;i++){
    double S=100*exp((r-pow(Sg,2)*0.5)*T+Sg*rnd.Gauss(0.,1.)*sqrt(T)); //Prezzo asset finale in modo diretto
    sum+=exp(-r*T)*fmax(0.,S-K); //prezzi opzione sommati per fare poi la media
    }
    ave[k]=sum/float(M/N); //Data blocking 100 valori del prezzo dell'opzione
    ave2[k]=pow(ave[k],2);
    k++;
  }
  
  //Da qui è progressione del data blocking per vedere come il valore simulato e l'errore migliorano all'aumentare di N
  ofstream Call_dir;
  Call_dir.open("Call_direct.dat");
  if(Call_dir.is_open()){
    k=0;
    while(k<N){
      for (int i=0;i<k+1;i++){
        sum_prog[k]+=ave[i];
        sum2_prog[k]+=ave2[i];
      }
      sum_prog[k]/=float(k+1);
      sum2_prog[k]/=float(k+1);
      err_prog[k]=error(sum_prog,sum2_prog,k);
      Call_dir<<sum_prog[k]<<" "<<err_prog[k]<<endl;
      k++;
    }
  }else cerr<<"ERROR: Unable to open Call_direct.dat"<<endl;
  Call_dir.close();


  //CALL DISCRETO
  //inizializzo i vettori
  for(int i=0;i<M/N;i++){
    ave[i]=0;
    ave2[i]=0;
    sum_prog[i]=0;
    sum2_prog[i]=0;
    err_prog[i]=0;    
  }

  int steps=100;
  k=0;
  while(k<N){
    double sum=0.;
    for(int i=0;i<M/N;i++){
      double S=100.;
      for(int j=0;j<steps;j++){ //prezzo asset finale in modo discreto
        S*=exp((r-pow(Sg,2)*0.5)*((j+1)/100.-j/100.)+Sg*rnd.Gauss(0.,1.)*sqrt((j+1)/100.-j/100.));
      }
      sum+=exp(-r*T)*fmax(0.,S-K); //prezzi opzione sommati per fare poi la media
    }
    ave[k]=sum/float(M/N); //Data blocking 100 valori del prezzo dell'opzione
    ave2[k]=pow(ave[k],2);
    k++;
  }

//Da qui è progressione del data blocking per vedere come il valore simulato e l'errore migliorano all'aumentare di N
  ofstream Call_discr;
  Call_discr.open("Call_discr.dat");
  if (Call_discr.is_open()){
    k=0;
    while(k<N){
      for(int i=0;i<k+1;i++){
        sum_prog[k]+=ave[i];
        sum2_prog[k]+=ave2[i];
      }
    sum_prog[k]/=(k+1);
    sum2_prog[k]/=(k+1);
    err_prog[k]=error(sum_prog,sum2_prog,k);
    Call_discr<<sum_prog[k]<<" "<<err_prog[k]<<endl;
    k++;
    }
  }else cerr<<"ERROR: Unable to open Call_discr.dat"<<endl;
  Call_discr.close();


//PUT DISCRETO
  //inizializzo i vettori
  for(int i=0;i<M/N;i++){
    ave[i]=0;
    ave2[i]=0;
    sum_prog[i]=0;
    sum2_prog[i]=0;
    err_prog[i]=0;    
  }

  k=0;
  while(k<N){
    double sum=0.;
    for(int i=0;i<M/N;i++){
      double S=100.;
      for(int j=0;j<steps;j++){ //prezzo asset finale in modo discreto
        S*=exp((r-pow(Sg,2)*0.5)*((j+1)/100.-j/100.)+Sg*rnd.Gauss(0.,1.)*sqrt((j+1)/100.-j/100.));
      }
      sum+=exp(-r*T)*fmax(0.,K-S); //prezzi opzione sommati per fare poi la media
    }
    ave[k]=sum/float(M/N); //Data blocking 100 valori del prezzo dell'opzione
    ave2[k]=pow(ave[k],2);
    k++;
  }

//Da qui è progressione del data blocking per vedere come il valore simulato e l'errore migliorano all'aumentare di N
  ofstream Put_discr;
  Put_discr.open("Put_discr.dat");
  if (Put_discr.is_open()){
    k=0;
    while(k<N){
      for(int i=0;i<k+1;i++){
        sum_prog[k]+=ave[i];
        sum2_prog[k]+=ave2[i];
      }
    sum_prog[k]/=(k+1);
    sum2_prog[k]/=(k+1);
    err_prog[k]=error(sum_prog,sum2_prog,k);
    Put_discr<<sum_prog[k]<<" "<<err_prog[k]<<endl;
    k++;
    }
  }else cerr<<"ERROR: Unable to open Put_discr.dat"<<endl;
  Put_discr.close();

//PUT DIRETTO
//inizializzo i vettori
  for(int i=0;i<M/N;i++){
    ave[i]=0;
    ave2[i]=0;
    sum_prog[i]=0;
    sum2_prog[i]=0;
    err_prog[i]=0;    
  }

  k=0;
  while(k<N){
    double sum=0.;
    for(int i=0;i<M/N;i++){
    double S=100*exp((r-pow(Sg,2)*0.5)*T+Sg*rnd.Gauss(0.,1.)*sqrt(T)); //Prezzo asset finale in modo diretto
    sum+=exp(-r*T)*fmax(0.,K-S); //prezzi opzione sommati per fare poi la media
    }
    ave[k]=sum/float(M/N); //Data blocking 100 valori del prezzo dell'opzione
    ave2[k]=pow(ave[k],2);
    k++;
  }
  
  //Da qui è progressione del data blocking per vedere come il valore simulato e l'errore migliorano all'aumentare di N
  ofstream Put_dir;
  Put_dir.open("Put_direct.dat");
  if(Put_dir.is_open()){
    k=0;
    while(k<N){
      for (int i=0;i<k+1;i++){
        sum_prog[k]+=ave[i];
        sum2_prog[k]+=ave2[i];
      }
      sum_prog[k]/=float(k+1);
      sum2_prog[k]/=float(k+1);
      err_prog[k]=error(sum_prog,sum2_prog,k);
      Put_dir<<sum_prog[k]<<" "<<err_prog[k]<<endl;
      k++;
    }
  }else cerr<<"ERROR: Unable to open Put_direct.dat"<<endl;
  Put_dir.close();

  return 0;
}
