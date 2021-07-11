#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "main.h"



int main (int argc, char *argv[]){

	// Random rnd;
	int seed[4];
	int p1, p2;
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

	

	//ESERCIZIO
   	//Da qui inizia il vero e proprio MonteCarlo Metropolis nei quattro casi.

   	//UNIFORME STATO FONDAMENTALE
   	out_prob.open("Psi.dat");
	x=0.,l=2.65;
	mu=0.8,s=0.6;
	accepted=0;
	for(int j=0;j<nblocks;j++){
		sum=0;
		cout<<j<<endl;
		for(int i=1;i<=steps/nblocks;++i){
			step_Uni();
			if(EQ_count>EQ_blocks-1){
				sum+=Ham();
				// cout<<Ham()<<endl;
			}
		}
		ave[j]=sum/double(steps/nblocks); //media per ogni blocco
		ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
		if(EQ_count==EQ_blocks-1) j=-1;
		EQ_count++;
	}
	out_prob.close();
	H=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
	print_ave(H,"Hamiltonian.dat",nblocks); //stampo i valori in un file
	cout<<"accettanza: "<<accepted/double(steps)<<endl;




/*
//scelta parametri mu e sigma
//FACENDO I CONTI SOTTO SI VEDE CHE MU=0.8 E SIGMA==0.62
	ofstream MuSigma;
	int counts_acc=0;
	double sum_acc=0.0;
	MuSigma.open("MuSigma.dat");
	mu=0.7,s=0.5;l=2.65,x=0.;
	while(s<0.7){
		while(mu<1.){
			accepted=0;
			EQ_count=0;
			for(int j=0;j<nblocks;j++){
				// cout<<j<<endl;
				sum=0;
				for(int i=1;i<=steps/nblocks;++i){
					step_Uni();
					if(EQ_count>EQ_blocks-1){
						sum+=Ham();
						// cout<<Ham()<<endl;
					}
				}
				ave[j]=sum/double(steps/nblocks); //media per ogni blocco
				ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
				if(EQ_count==EQ_blocks-1) j=-1;
				EQ_count++;
			}
			H=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
			MuSigma<<H.sum_prog[nblocks-1]<<" "<<mu<<" "<<s<<endl;
			cout<<" "<<s<<" "<<mu<<" acc: "<<accepted/(double)steps<<endl;
			sum_acc+=accepted/(double)steps;
			counts_acc++;
			mu+=0.01;
		}
		mu=0.7;
		s+=0.01;
	}
	cout<<"sum_acc: "<<sum_acc/(double)counts_acc<<endl;
	MuSigma.close();
*/

	return 0;
}





//FUNCTION
double PsiTrial(double cx){
	// cout<<"PsiTrial"<<pow(exp(-pow(cx-mu,2)/(2*s*s))+exp(-pow(cx+mu,2)/(2*s*s)),2)<<endl;
	return exp(-pow(cx-mu,2)/(s*s)) + exp(-pow(cx+mu,2)/(s*s)) + 2*exp((-pow(cx-mu,2)-pow(cx+mu,2))/(2*s*s));
}

double Pot(void){
	return pow(x,4)-5*0.5*x*x;
}

double Ham(void){
	double Psi_a=exp(-pow(x-mu,2)/(2*s*s));
	double Psi_b=exp(-pow(x+mu,2)/(2*s*s));
	// cout<<6/(double)steps*(-1/(2*s*s)*(Psi_a*pow(x-mu,2)/(s*s)+Psi_b*pow(x+mu,2)/(s*s)-Psi_a-Psi_b)+Pot(cx))/(Psi_a+Psi_b)<<endl;
	return ( -1/(2*s*s) * (Psi_a*pow(x-mu,2)/(s*s) + Psi_b*pow(x+mu,2)/(s*s) - (Psi_a+Psi_b))  +  Pot()*(Psi_a+Psi_b) )  / (Psi_a+Psi_b);
	// return ( -1/(2*s*s) * (Psi_a*pow(x-mu,2)/(s*s) + Psi_b*pow(x+mu,2)/(s*s) - (Psi_a+Psi_b)) )  / (Psi_a+Psi_b);
}


//Queste due che seguono sono il passo del Metropolis con il rejection sampling.
void step_Uni(void){
	xnew=x+2*l*rnd.Rannyu()-l;

	// cout<<"b: "<<Psi_b<<" a:"<<Psi_a<<endl;
	if(EQ_count>EQ_blocks-1){
		out_prob<<x<<endl;
	}

	acc=fmin(1,PsiTrial(xnew)/PsiTrial(x)); //probabilità legata dello step successivo per il rejection sampling
	p=rnd.Rannyu(); //genero un numero casuale tra 0 e acc massima che essendo normalizzata ha massimo 1.
	// cout<<acc<<"   "<<p<<endl;
	if(p<acc){ //rejection sampling se il numero casuale è minore della prob di accettazione allora accetta.
		x=xnew;
		if(EQ_count>EQ_blocks-1) accepted++;
	}
	return;
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

double error(double *AV,double *AV2,int n){
	if (n==0) return 0;
	else {
		return sqrt((AV2[n]-pow(AV[n],2))/n);
	}
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


