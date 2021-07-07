#include<iostream>
#include<fstream>


using namespace std;
Random rnd;

//simulation
const int steps=5000000;
const int nblocks=100;
double l; //tutti i passi dei quattro casi sono stati scelti in modo che il numero di posizioni nuove accettate fosse circa il 50% di quelle proposte.
double x,y,z;//Parto dal raggio di Bhor
double xnew,ynew,znew,R,acc,p;
int EQ_count=0,EQ_blocks=10;

//correlation check
const int steps_corr=1000000;
int EQ_count_corr=0,EQ_steps_corr=500000,check=0,num_steps_corr=0;
double dist[steps_corr],dist_reci[steps_corr];

//blocks average
double sum;
double ave[steps/nblocks],ave2[steps/nblocks];
struct prog_ave{
	double sum_prog[nblocks]={0};
	double sum2_prog[nblocks]={0};
	double err_prog[nblocks]={0};
};
prog_ave R1_unif;
prog_ave R2_unif;
prog_ave R1_Gauss;
prog_ave R2_Gauss;

//equilibrium check
int EQ_steps,EQ_nblocks;

//near and far trial
int NF_steps=10000,NF_nblocks=100;

//function
double phi1(double ,double , double );
double phi2(double ,double , double );

void step_Uni(double (* function)(double,double,double));
void step_Gauss(double (* function)(double,double,double));

prog_ave prog(double *, double *, int);
double error(double *,double *, int);
void print_ave(prog_ave,string,int);

void MesuAndPrint_NumStepsCorr(string);

void input_EQ(double,int,int);	
void UnifEqCheck(double (* function)(double,double ,double),string);
void GaussEqCheck(double (* function)(double,double ,double),string);

void NF_trial(void);







