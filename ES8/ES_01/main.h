#include<iostream>
#include<fstream>


using namespace std;
Random rnd;

//simulation
const int steps=1000000;
const int nblocks=100;
double l; //tutti i passi dei quattro casi sono stati scelti in modo che il numero di posizioni nuove accettate fosse circa il 50% di quelle proposte.
double x;//Parto dal raggio di Bhor
double xnew,acc,p;
double U;
int EQ_count=0,EQ_blocks=10;
int accepted;

// //correlation check
// const int steps_corr=1000000;
// int EQ_count_corr=0,EQ_steps_corr=500000,check=0,num_steps_corr=0;
// double dist[steps_corr],dist_reci[steps_corr];

//blocks average
double sum;
double ave[steps/nblocks],ave2[steps/nblocks];
struct prog_ave{
	double sum_prog[nblocks]={0};
	double sum2_prog[nblocks]={0};
	double err_prog[nblocks]={0};
};
prog_ave H;

//Parameters
double mu,s;
ofstream out_prob;





//equilibrium check
// int EQ_steps,EQ_nblocks;

//near and far trial
// int NF_steps=10000,NF_nblocks=100;

//function
double PsiTrial(double);
double Ham(void);
double Pot(void);

void step_Uni(void);


prog_ave prog(double *, double *, int);
double error(double *,double *, int);
void print_ave(prog_ave,string,int);










