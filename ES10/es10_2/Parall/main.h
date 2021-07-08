#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <iomanip>
#include "random.h"
#include "population.h"

using namespace std;

//Variables
int n_cities=32,dim=3;
int n_Ind=200;
int n_gen=3500;
int n_migr=500;

vector <vector <double> > cities; //vettore delle citta
vector <vector <double> > CitiesTrial;


//Individui
int One,Two,control;
vector <Individual> VecInd; //vettore di individui

//SelectInd
double p=1.7;

//PRINT
ofstream BestPath;
ofstream pro1,pro2,pro3,pro4;

//Random numbers
Random rnd;
Random rndGlobal;



//Function
Random SetRandom(Random, int);
vector <vector <double> > CityVectorCirc(void);
vector <vector <double> > CityVectorSquare(void);
void ReadCityVector(string );
Population FirstPopulation(int , vector <vector <double> > );







