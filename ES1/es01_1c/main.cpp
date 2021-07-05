
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

void SetRandom(void);
 
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


   // ESERCIZIO c)
   int M=100;
   int n=10000;
   float chi2[100]={0};
   ofstream chiquadro;
   chiquadro.open("chi2.dat");
   if (chiquadro.is_open()){
      for(int k=0;k<100;k++){ //questo ripete quello che si fa dentro 100, così ottengo 100 chiquadro.
         int Num[100]={0};   
         for(int i=0;i<n;i++){ 
            float x=rnd.Rannyu(); //genero 10mila numeri random unif. tra zero e uno.
            for( int j=0;j<M;j++){ //qui conto quanti ce ne sono in ognuno dei cento intervalli nel vettore Num[j]
               if(x>j/100.0 && x<(j+1)/100.0){
                  Num[j]++;
               }
            }
         }
         for (int i=0;i<M;i++){ //trovo il chi2 
            chi2[k]+=pow(Num[i]-n/M,2)/(n/M);
         }
      chiquadro<<chi2[k]<<endl;
      }
   }
   chiquadro.close();
   return 0;
}

