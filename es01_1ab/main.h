#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

//Variables
int const M=100000,N=100,L=M/N;

//Random
Random rnd;
int seed[4];
int p1, p2;
 
//blocks average
double sum;
double ave[L],ave2[L];
struct prog_ave{
	double sum_prog[N]={0};
	double sum2_prog[N]={0};
	double err_prog[N]={0};
};
prog_ave r1;
prog_ave r2;


//function
void SetRandom(void);
double error(double *,double *,int );
prog_ave prog(double *, double *, int);
void print_ave(prog_ave,string,int);


