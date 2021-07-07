#include<iostream>
#include<fstream>
#include "population.h"
#include "random.h"

using namespace std;

Population::Population(vector <Individual> x){
	Pop=x;
	CalFitness();
	OrdByFit();
	SetRandom();
	
}


void Population::SetRandom(void){
	Random rnd;
	int seed[4];
	int p1,p2;
	
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

	r=rnd;
	return;
}


void Population::OrdByFit(void){
	for(int i=0;i<Pop.size();++i){
		for(int j=i+1;j<Pop.size();++j){
			if(Pop[i].Fitness<Pop[j].Fitness) swap(Pop[i],Pop[j]);
		}
	}
	return;
}


void Population::CalFitness(void){
	double sum=0.0;
	
	for (int i = 0; i < Pop.size(); ++i){
		sum += Pop[i].PathLength;
	}

	for (int i = 0; i < Pop.size(); ++i)	{
		Pop[i].Fitness = 1. - Pop[i].PathLength / sum;
	}

	return;
}

int Population::SelectInd(double p){
	int j= (int) Pop.size()*(pow(r.Rannyu(),p));
	return j;
}


pair<Individual,Individual> Population::CrossOver(int OneInd, int TwoInd){

	if(TwoInd==OneInd){ 
		cerr<<"PROBLEMA: Hai selezionato due individui uguali per il Crossover"<<endl;
		for(int i=0;i<Pop[OneInd].Path.size()-1;++i){
			cout<<Pop[OneInd].Path[i][2]<<" ";
		}
		cout<<endl;
		for(int i=0;i<Pop[TwoInd].Path.size()-1;++i){
			cout<<Pop[TwoInd].Path[i][2];
		}
		terminate();
	}

	int cut=r.Rannyu()*(Pop[OneInd].Path.size()-4)+1.5;
	
	vector <vector <double>> OnePos;
	vector <vector <double>> TwoPos;
	for(int i=0;i<Pop[OneInd].Path.size()-1-cut;++i){
		vector <double> Onev;
		vector <double> Twov;
		for(int j=0;j<Pop[OneInd].Path.size();++j){
			if(Pop[OneInd].Path[cut+i][2]==Pop[TwoInd].Path[j][2]){
				Onev.push_back(Pop[OneInd].Path[cut+i][0]);
				Onev.push_back(Pop[OneInd].Path[cut+i][1]);
				Onev.push_back(Pop[OneInd].Path[cut+i][2]);
				Onev.push_back(j);
			}
			if(Pop[TwoInd].Path[cut+i][2]==Pop[OneInd].Path[j][2]){
				Twov.push_back(Pop[TwoInd].Path[cut+i][0]);
				Twov.push_back(Pop[TwoInd].Path[cut+i][1]);
				Twov.push_back(Pop[TwoInd].Path[cut+i][2]);
				Twov.push_back(j);
			}
		}
		OnePos.push_back(Onev);
		TwoPos.push_back(Twov);
	}
	
	sort(OnePos.begin(),OnePos.end(),[](const vector <double> &a,const vector <double> &b) { return a[3]<b[3]; } );
	sort(TwoPos.begin(),TwoPos.end(),[](const vector <double> &a,const vector <double> &b) { return a[3]<b[3]; } );

	pair<Individual,Individual> Sons (Pop[OneInd],Pop[TwoInd]);
	
	
	for(int i=0;i<Sons.first.Path.size()-1-cut;++i){
		Sons.first.Path[cut+i][0]=OnePos[i][0];
		Sons.second.Path[cut+i][0]=TwoPos[i][0];
		
		Sons.first.Path[cut+i][1]=OnePos[i][1];
		Sons.second.Path[cut+i][1]=TwoPos[i][1];
		
		Sons.first.Path[cut+i][2]=OnePos[i][2];
		Sons.second.Path[cut+i][2]=TwoPos[i][2];
	}
	
 	Sons.first.UpdateInd();
	Sons.second.UpdateInd();

	
	return Sons;
}


pair <Individual,Individual> Population::NoCrossOver(int OneInd, int TwoInd){
	
	pair<Individual,Individual> Sons (Pop[OneInd],Pop[TwoInd]);

	if(TwoInd==OneInd){
		cerr<<"PROBLEMA: Hai selezionato due individui uguali per il Crossover"<<endl;
		for(int i=0;i<Sons.first.Path.size()-1;++i){
			cout<<Sons.first.Path[i][2]<<" ";
		}
		cout<<endl;
		for(int i=0;i<Sons.second.Path.size()-1;++i){
			cout<<Sons.second.Path[i][2];
		}
		return Sons;
	}


	return Sons;
}

