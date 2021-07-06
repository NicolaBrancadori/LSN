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
int B_trial_2(double x){
  if (x<0.5) return 0;
  else return 1;
}
int B_trial_3(double x){
  if (x<1./3.) return 0;
  else if (x>1./3. && x<2./3.) return 1;
  else return 2;
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


  int M=10000;
  int N=100;
  int a=1;
  int Ber_3;
  double sum=0;
  double sum2=0;
  double ave[100];
  double ave2[100];
  double r_N[100]={0};
  double err[100]={0};
  int steps=0;
  ofstream Res;
  Res.open("Risultati.dat");
  if (Res.is_open()){
    while(steps<100){ //ripeto quello che c'è dentro per random walk con steps crescente da 1 a 100.
      int k=0;
      while(k<N){ //cicla sui blocchi per ottenere N medie della norma di r.
        sum=0;
        for(int j=0;j<M/N;j++){ //ottengo cento r posizioni finali.
          int RWx=0;
          int RWy=0;
          int RWz=0;
          for(int i=0;i<steps+1;i++){ //qua dentro simulo il random walk con steps passi.
            Ber_3=B_trial_3(rnd.Rannyu());
            if(i>0 && Ber_3==0){
              RWx=RWx+2*a*(B_trial_2(rnd.Rannyu())-0.5);
            }
            else if(i>0 && Ber_3==1){
              RWy=RWy+2*a*(B_trial_2(rnd.Rannyu())-0.5);
            }
            else if(i>0 && Ber_3==2){
              RWz=RWz+2*a*(B_trial_2(rnd.Rannyu())-0.5);
            }
          }
          sum+=sqrt(pow(RWx,2)+pow(RWy,2)+pow(RWz,2)); //alla fine di ogni simulazione sommo la norma di r.
        }
        ave[k]=sum/float(M/N);//qui faccio la media su ogni blocco ottengo quindi N medie della norma di r.
        ave2[k]=pow(ave[k],2); //questi sono i quadrati delle medie.
        k++;
      }
      sum=0;
      sum2=0;
      for(int i=0;i<N;i++){
        sum+=ave[i];
        sum2+=ave2[i];
      }
      r_N[steps]=sum/float(N); //media delle medie della norma di r una per ogni random walk con steps passi.
      err[steps]=sqrt(sum2/float(N) - pow(sum/float(N),2)); //l'errore sulla media delle medie per ogni random walk con staps passi.
      Res<<r_N[steps]<<" "<<err[steps]<<endl;
      steps++;
    }
  }
  else {cerr<<"PROBLEM: Unable to open Risultati.dat"<<endl;}
  Res.close();
  return 0;
}


