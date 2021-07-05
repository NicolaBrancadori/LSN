
#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include <cmath>

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

  int M=10000;
  double sum_10;
  double sum_100;
  ofstream espo;
  ofstream Lore;
  ofstream gauss;

  //CASO ESPONENZIALE 
  espo.open("espo.dat");
  if (espo.is_open()){
    for(int i=0;i<M;i++){ //qui creo le 10^4 somme
      espo<<rnd.Exp(1.);  //che in questo caso sono uguali ai variabili random
      espo<<" "<<(rnd.Exp(1.)+rnd.Exp(1.))/2; //in questo caso sono la media di due variabili random
      sum_10=0;
      for(int j=0;j<10;j++){ 
        sum_10+=rnd.Exp(1.); 
      }
      espo<<" "<<sum_10/10; //in questo caso son la media di 10 variabili random
      sum_100=0;
      for(int k=0;k<100;k++){ 
        sum_100+=rnd.Exp(1.);
      }
      espo<<" "<<sum_100/100<<endl; //in questo caso sono la media di 100 variabili random
    }
  } else cerr<<"PROBLEM: Unable to open espo.dat"<<endl;
  espo.close();
  
  // I seguenti casi sono analoghi al primo.

  //CASO LORENTZIANO
  Lore.open("Lore.dat");
  if (Lore.is_open()){
    for(int i=0;i<M;i++){
      Lore<<rnd.Lorentz(1.,0.);
      Lore<<" "<<(rnd.Lorentz(1.,0.)+rnd.Lorentz(1.,0.))/2.;
      sum_10=0;
      for(int j=0;j<10;j++){
        sum_10+=rnd.Lorentz(1.,0.);
      }
      Lore<<" "<<sum_10/10;
      sum_100=0;
      for(int k=0;k<100;k++){
        sum_100+=rnd.Lorentz(1.,0.);
      }
      Lore<<" "<<sum_100/100<<endl;
    }
  } else cerr<<"PROBLEM: Unable to open Lore.dat"<<endl;
  Lore.close();  
  
  //CASO GAUSSIANO
  gauss.open("gauss.dat");
  if (gauss.is_open()){
    for(int i=0;i<M;i++){
      gauss<<rnd.Gauss(0,2);
      gauss<<" "<<(rnd.Gauss(0,2)+rnd.Gauss(0,2))/2.;
      sum_10=0;
      for(int j=0;j<10;j++){
        sum_10+=rnd.Gauss(0,2);
      }
      gauss<<" "<<sum_10/10;
      sum_100=0;
      for(int k=0;k<100;k++){
        sum_100+=rnd.Gauss(0,2);
      }
      gauss<<" "<<sum_100/100<<endl;
    }
  } else cerr<<"PROBLEM: Unable to open gauss.dat"<<endl;
  gauss.close();  

  
  return 0;
}
