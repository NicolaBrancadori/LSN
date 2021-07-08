#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <iomanip>
#include "random.h"
#include "individual.h"



using namespace std;

//Variables
int n_cities=32,dim=3;
double Temp=70.,DL;
double beta=1/Temp;

//MC Metropolis
int nsteps=1000000;
double p;//probabilità di accettazione
int accepted,proposed;

//Print
ofstream out_BestInd,out_BestPath;


vector <vector <double> > cities; //vettore delle citta

//Random numbers
Random rnd;
int p1, p2;
int seed[4];


//Function
void SetRandom(void);
vector <vector <double> > CityVectorCirc(void);
vector <vector <double> > CityVectorSquare(void);
Individual CallPerm(Individual);
double BoltzWeight(Individual,Individual);







