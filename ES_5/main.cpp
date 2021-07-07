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

	
/*
	//Controllo del numero si step necessari per andare all'equilibrio
	input_EQ(1.22,500000,100);
	UnifEqCheck(&phi1,"EqCheck_U1.dat");

	input_EQ(2.98,500000,100);
	UnifEqCheck(&phi2,"EqCheck_U2.dat");

	input_EQ(0.76,500000,100);
	UnifEqCheck(&phi1,"EqCheck_G1.dat");

	input_EQ(1.87,500000,100);
	UnifEqCheck(&phi2,"EqCheck_G2.dat");
*/	




/*
	//Questa prima parte è il codice per contare il numero di step necessari affinchè due posizioni siano a distanza maggiore di a0.
	//E l'ho fatto nei quattro casi.
	x=1.,y=1.,z=1.;
	l=1.22;
	for(int j=0;j<steps_corr;++j){
		if(EQ_count_corr>EQ_steps_corr){
			dist[j]=R;
		} 		
		step_Uni(&phi1);
		
		if(EQ_count_corr==EQ_steps_corr) j=-1;
		EQ_count_corr++;
	}
	
	MesuAndPrint_NumStepsCorr("NumberOfCorrStep_U1.dat");

	x=1.,y=1.,z=1.;
	l=2.98;
	for(int j=0;j<steps_corr;++j){
		if(EQ_count_corr>EQ_steps_corr){
			dist[j]=R;
		} 		
		step_Uni(&phi2);
		
		if(EQ_count_corr==EQ_steps_corr) j=-1;
		EQ_count_corr++;
	}
	
	MesuAndPrint_NumStepsCorr("NumberOfCorrStep_U2.dat");

	x=1.,y=1.,z=1.;
	l=0.76;
	for(int j=0;j<steps_corr;++j){
		if(EQ_count_corr>EQ_steps_corr){
			dist[j]=R;
		} 		
		step_Gauss(&phi1);
		
		if(EQ_count_corr==EQ_steps_corr) j=-1;
		EQ_count_corr++;
	}
	
	MesuAndPrint_NumStepsCorr("NumberOfCorrStep_G1.dat");

	x=1.,y=1.,z=1.;
	l=1.87;
	for(int j=0;j<steps_corr;++j){
		if(EQ_count_corr>EQ_steps_corr){
			dist[j]=R;
		} 		
		step_Gauss(&phi2);
		
		if(EQ_count_corr==EQ_steps_corr) j=-1;
		EQ_count_corr++;
	}

	MesuAndPrint_NumStepsCorr("NumberOfCorrStep_G2.dat");
*/

	

	//Ho utilizzato la seguente funzione per far vedere la differenze tra partire da lontano e da vicino.
	//NF_trial();


	

	//ESERCIZIO
   	//Da qui inizia il vero e proprio MonteCarlo Metropolis nei quattro casi.

   	//UNIFORME STATO FONDAMENTALE
	x=1.,y=1.,z=1.;
	l=1.22;
	for(int j=0;j<nblocks;j++){
		sum=0;
		for(int i=1;i<=steps/nblocks;++i){
			step_Uni(&phi1);
			if(EQ_count>EQ_blocks-1) sum+=R;
			
		}
		ave[j]=sum/double(steps/nblocks); //media per ogni blocco
		ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
		if(EQ_count==EQ_blocks-1) j=-1;
		EQ_count++;
	}

	R1_unif=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
	print_ave(R1_unif,"Uniforme_1.dat",nblocks); //stampo i valori in un file
	
	
	//UNIFORME PRIMO STATO ECCITATO
	EQ_count=0;
	x=1.,y=1.,z=1.;
	l=2.98;
	for(int j=0;j<nblocks;++j){
		sum=0;
		for(int i=1;i<steps/nblocks;++i){
			if(EQ_count>EQ_blocks-1) sum+=R;
			step_Uni(&phi2);
		}
	
		ave[j]=sum/double(steps/nblocks); //media per ogni blocco
		ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
	
		if(EQ_count==EQ_blocks-1) j=-1;
		EQ_count++;
	}
	
	R2_unif=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
	print_ave(R2_unif,"Uniforme_2.dat",nblocks); //stampo i valori in un file

	
	//GAUSS STATO FONDAMENTALE
	EQ_count=0;
	x=1.,y=1.,z=1.;
	l=0.76;
	for(int j=0;j<nblocks;j++){
		sum=0;
		for(int i=1;i<steps/nblocks;++i){
			if(EQ_count>EQ_blocks-1) sum+=R;
			step_Gauss(&phi1);
		}
		
		ave[j]=sum/double(steps/nblocks); //media per ogni blocco
		ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
		
		if(EQ_count==EQ_blocks-1) j=-1;
		EQ_count++;
	}
	
	R1_Gauss=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
	print_ave(R1_Gauss,"Gauss_1.dat",nblocks); //stampo i valori in un file	
	
	
	//GAUSS PRIMO STATO ECCITATO
	EQ_count=0;
	x=1.,y=1.,z=1.;
	l=1.87;
	for(int j=0;j<nblocks;j++){
		sum=0;
		for(int i=1;i<steps/nblocks;++i){
			if(EQ_count>EQ_blocks-1) sum+=R;
			step_Gauss(&phi2);
		}
		
		ave[j]=sum/double(steps/nblocks); //media per ogni blocco
		ave2[j]=pow(ave[j],2);	//quadrato della media per ogni blocco
		
		if(EQ_count==EQ_blocks-1) j=-1;
		EQ_count++;
	}

	R2_Gauss=prog(ave,ave2,nblocks); //misuro le somme progressive e l'errore progressivo e li metto nella struct prog_ave
	print_ave(R2_Gauss,"Gauss_2.dat",nblocks); //stampo i valori in un file	

	return 0;
}



//FUNCTION
double phi1(double cx,double cy, double cz){
	return exp(-2*sqrt(cx*cx+cy*cy+cz*cz));
}

double phi2(double cx,double cy, double cz){
	return cz*cz*exp(-sqrt(cx*cx+cy*cy+cz*cz));
}
//Queste due che seguono sono il passo del Metropolis con il rejection sampling.
void step_Uni(double (* function)(double,double,double)){
	xnew=x+2*l*rnd.Rannyu()-l;
	ynew=y+2*l*rnd.Rannyu()-l;
	znew=z+2*l*rnd.Rannyu()-l;

	R=sqrt(x*x+y*y+z*z);
	acc=fmin(1,function(xnew,ynew,znew)/function(x,y,z)); //probabilità legata dello step successivo per il rejection sampling
	p=rnd.Rannyu(); //genero un numero casuale tra 0 e acc massima che essendo normalizzata ha massimo 1.
	
	if(p<acc){ //rejection sampling se il numero casuale è minore della prob di accettazione allora accetta.
		x=xnew;
		y=ynew;
		z=znew;
	}
	return;
}

void step_Gauss(double (* function)(double,double,double)){

	xnew=x+rnd.Gauss(0.,l);
	ynew=y+rnd.Gauss(0.,l);
	znew=z+rnd.Gauss(0.,l);
	
	R=sqrt(x*x+y*y+z*z);
	acc=fmin(1,function(xnew,ynew,znew)/function(x,y,z)); //probabilità legata dello step successivo per il rejection sampling
	p=rnd.Rannyu(); //genero un numero casuale tra 0 e acc massima che essendo normalizzata ha massimo 1.
	
	if(p<acc){ //rejection sampling se il numero casuale è minore della prob di accettazione allora accetta.
		x=xnew;
		y=ynew;
		z=znew;
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

void MesuAndPrint_NumStepsCorr(string filename2){
	ofstream out;
	out.open(filename2);
	if(out.is_open()){
		for(int i=0;i<steps_corr;++i){
			dist_reci[i]=abs(dist[i]-dist[check]);
			num_steps_corr++;
			if (dist_reci[i]>1.){
				out<<num_steps_corr<<endl;
				check=i;
				num_steps_corr=0;
			}
		}
	} else cerr<<"PROBLEM: Unable to open"<<filename2<<endl;
	out.close();
	check=0,num_steps_corr=0,EQ_count_corr=0;
	
	return;
}


void input_EQ(double set_l,int set_EQsteps, int set_EQnblocks){
	x=1.,y=1.,z=1.;
	l=set_l;
	EQ_steps=set_EQsteps;
	EQ_nblocks=set_EQnblocks;
	
	return;
}

void UnifEqCheck(double (* function)(double,double ,double),string filename3){
	double EqAve[EQ_nblocks],EqAve2[EQ_nblocks];
	for(int i=0;i<EQ_nblocks;++i){
		sum=0;
		for(int j=0;j<EQ_steps/EQ_nblocks;++j){
			sum+=R;
			step_Uni(function);
		}

	EqAve[i]=sum/double(EQ_steps/EQ_nblocks);
	EqAve2[i]=pow(EqAve[i],2);
	}
	
	prog_ave EQ=prog(EqAve,EqAve2,EQ_nblocks);
	print_ave(EQ,filename3,EQ_nblocks);
	return;
}

void GaussEqCheck(double (* function)(double,double ,double),string filename4){
	double EqAve[EQ_nblocks],EqAve2[EQ_nblocks];
	for(int i=0;i<EQ_nblocks;++i){
		sum=0;
		for(int j=0;j<EQ_steps/EQ_nblocks;++j){
			sum+=R;
			step_Gauss(function);
		}

	EqAve[i]=sum/double(EQ_steps/EQ_nblocks);
	EqAve2[i]=pow(EqAve[i],2);
	}
	
	prog_ave EQ=prog(EqAve,EqAve2,EQ_nblocks);
	print_ave(EQ,filename4,EQ_nblocks);
	return;
}

void NF_trial(void){
	double NF_ave[NF_nblocks],NF_ave2[NF_nblocks];
	l=1.22;
	
	x=1.,y=1.,z=1.;
	for(int i=0;i<NF_nblocks;++i){
		sum=0;
		for(int j=0;j<NF_steps/NF_nblocks;++j){
			step_Uni(&phi1);
			sum+=R;
		}
		NF_ave[i]=sum/double(NF_steps/NF_nblocks);
		NF_ave2[i]=pow(NF_ave[i],2);
	}
	
	prog_ave near=prog(NF_ave,NF_ave2,NF_nblocks);
	print_ave(near,"U1_near.dat",NF_nblocks);
	
	x=10.,y=10.,z=10.;
	for(int i=0;i<NF_nblocks;++i){
		sum=0;
		for(int j=0;j<NF_steps/NF_nblocks;++j){
			step_Uni(&phi1);
			sum+=R;
		}
		NF_ave[i]=sum/double(NF_steps/NF_nblocks);
		NF_ave2[i]=pow(NF_ave[i],2);
	}
	
	prog_ave far=prog(NF_ave,NF_ave2,NF_nblocks);
	print_ave(far,"U1_far.dat",NF_nblocks);
	
	
}
	



