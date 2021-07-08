
#ifndef individual_H
#define individual_H

#include <vector>
#include <cmath>
#include "random.h"

using namespace std;



class Individual{

public:
	vector < vector<double> > Path;
	Random R;
	double PathLength;//L
	bool Check;//Se True l'individuo è buono altrimenti non rispetta i criteri.

	Individual(vector< vector<double> > ); //costruttore
	~Individual(){}


	
//Metodi
	void CalPathLength() ;//Calcola L
	void CalCheck();//Controlla che l'individuo sia buono
	void UpdateInd();//Ricalcola L e Check e Fitness a zero

	//Mutazioni Genetiche
	void P1(void);//Permutazione di una città
	void P2(void);//shift di n citta per m citta consecutive 
	void P3(void);//permutazione di m citta con m altre citta
	void P4(void);//inversione dell'ordine di m citta 
	
	//Random
	void SetRandom(void);
};



#endif 	