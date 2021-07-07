#ifndef population_H
#define population_H

#include<vector>
#include<utility>
#include "individual.h"

using namespace std;

class Population{

public:
	vector <Individual> Pop;
	Random r;


	Population(vector <Individual> );
	~Population(void){};
	




//METODI
	void CalFitness(void); //Calcola il Fitness di ogni individuo
	void OrdByFit(void); //Ordina la popolazione in ordine decrescente di fitness
	int SelectInd(double ); //selezione l'individuo a seconda di quanto sia alto il fitness

	//Crossover
	pair <Individual,Individual> CrossOver(int ,int );//CrossOver
	pair <Individual,Individual> NoCrossOver(int, int);//Se non avviene il CrossOver

	//Random
	void SetRandom(void);

};





#endif 