#include "main.h"


int main (){

SetRandom();

// ESERCIZIO a)
  // calcolo la media e la media al quadrato per ogni blocco e la metto in un vettore
    for(int i=0;i<N;i++){
      sum=0;
      for(int j=0;j<L;j++){
        sum+=rnd.Rannyu();
      }
      ave[i]=sum/L;
      ave2[i]=pow(sum/L,2);
    }
  /* qui invece sto facendo la somma delle medie per un numero crescente di blocchi, prima 2 blocchi, poi 3, poi N.
  Questo per vedere come varia la stima del valore atteso e l'errore al crescere di M e quindi di N*/
  r1 = prog(ave,ave2,N);
  print_ave(r1,"risultati_a.dat",N);

// ESERCIZIO  b)
  for (int i=0;i<N;i++){
    sum=0;
    for(int j=0;j<L;j++){
      sum+=pow((rnd.Rannyu()-0.5),2);
    }
    ave[i]=sum/L;
    ave2[i]=pow(sum/L,2);
  }
  
  r2 = prog(ave,ave2,N);
  print_ave(r2,"risultati_b.dat",N);

  
  return 0;
}


void SetRandom(void){
// imposto il generatore random
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


double error(double * AV,double * AV2,int n){
  if (n==0) return 0;
  else{
    return sqrt((AV2[n]-AV[n]*AV[n])/n);
  }
}

prog_ave prog(double *AVE,double *AVE2,int nblocks){
  prog_ave ave;
  for(int i=0;i<nblocks;++i){
    for(int k=0;k<i+1;++k){
      ave.sum_prog[i]+=AVE[k];
      ave.sum2_prog[i]+=AVE2[k];
    }
  ave.sum_prog[i]/=(i+1);
  ave.sum2_prog[i]/=(i+1);
  ave.err_prog[i]=error(ave.sum_prog,ave.sum2_prog,i);
  }
  return ave;
}

void print_ave(prog_ave AVE,string filename1,int nblocks){
  ofstream out;
  out.open(filename1);
  if(out.is_open()){
    for(int i=0;i<nblocks;++i){
      out<<AVE.sum_prog[i]<<" "<<AVE.err_prog[i]<<endl;
    }
  }else cerr<<"PROBLEM: Unable to open "<<filename1<<endl;
  out.close();
  return;
}




