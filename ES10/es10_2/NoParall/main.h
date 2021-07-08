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
int n_Ind=600;
int n_gen=1300;

vector <vector <double> > cities; //vettore delle citta


//Individui
int One,Two,control;
vector <Individual> VecInd; //vettore di individui

//SelectInd
double p=1.7;

//PRINT
ofstream BestPath;

//Random numbers
Random rnd;
int p1, p2;
int seed[4];


//Function
void SetRandom(void);
vector <vector <double> > CityVectorCirc(void);
vector <vector <double> > CityVectorSquare(void);
void ReadCityVector(string );
Population FirstPopulation(int , vector <vector <double> > );







