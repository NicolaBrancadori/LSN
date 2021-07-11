/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>     // srand, rand: to generate random number
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include <string>
#include "MolDyn_NVE.h"

using namespace std;

int main(){ 
	Input();//Inizialization
	string opt;
	cout<<"Insert 'yes' if you want to scale the velocity to match the desired temperature "<<endl<<endl;
	cin>>opt;

	for(istep=1; istep <= nstep; ++istep){
		Move();//Move particles with Verlet algorithm
		if(opt=="yes"){
			Vel_Rescale();
			istep=1;
			opt="no";
			cout<<"Velocity rescaled"<<endl;
		}
		if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
		if(istep%10 == 0){
			Measure();//Properties measurement
			sum_T+=stima_temp;
			sum_E+=stima_etot;
			sum_U+=stima_pot;
			sum_K+=stima_kin;
			sum_P+=stima_pres;
			for(int i =0;i<nbins;++i){
				sum_GR[i] += stima_gr[i];
				gr[i]=0;
			}

			
			//ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"! 
			if(nconf%10==0){
				average();
				sum_T=0.;
				sum_E=0.;
				sum_U=0.;
				sum_K=0.;
				sum_P=0.;
				for(int i=0;i<nbins;++i) sum_GR[i]=0;
			}
			nconf += 1;
		}
		if(istep==nstep-1) Conf_old0();
	}
	cout<<endl<<"The penultimate configuration to restart has been printed to file old.0"<<endl;
	ConfFinal();//Write final configuration to re

	ofstream aveGR_out;
	aveGR_out.open("ave_gave.0");
	for(int i=0;i<nbins;++i){
		double col[nblocks];
		double col2[nblocks];
		for(int j=0;j<nblocks;++j){
			col[j]=ave_GR[j][i];
			col2[j]=ave2_GR[j][i];
		}
	Prog_ave_GR=prog(col,col2,nblocks);
	aveGR_out<<Prog_ave_GR.sum_prog[nblocks-1]<<" "<<Prog_ave_GR.err_prog[nblocks-1]<<endl;
	}
	aveGR_out.close();


	Prog_ave_T= prog(ave_T,ave2_T,nblocks);
	Prog_ave_E= prog(ave_E,ave2_E,nblocks);
	Prog_ave_U= prog(ave_U,ave2_U,nblocks);
	Prog_ave_K= prog(ave_K,ave2_K,nblocks);
	Prog_ave_P= prog(ave_P,ave2_P,nblocks);

	
	
	Print_prog_ave();
	
	return 0;
}


void Input(void){ //Prepare all stuff for the simulation
	ifstream ReadInput,ReadConf,ReadConfT_deltaT;
	double ep, ek, pr, et, vir;

	cout << "Classic Lennard-Jones fluid        " << endl;
	cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
	cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
	cout << "The program uses Lennard-Jones units " << endl;

	seed = 1;    //Set seed for random numbers
	srand(seed); //Initialize random number generator
  
	ReadInput.open("input.dat"); //Read input

	ReadInput >> temp;

	ReadInput >> npart;
	cout << "Number of particles = " << npart << endl;

	ReadInput >> rho;
	cout << "Density of particles = " << rho << endl;
	vol = (double)npart/rho;
	cout << "Volume of the simulation box = " << vol << endl;
	box = pow(vol,1.0/3.0);
	cout << "Edge of the simulation box = " << box << endl;

	ReadInput >> rcut;
	ReadInput >> delta;
	ReadInput >> nstep;
	ReadInput >> iprint;

	cout << "The program integrates Newton equations with the Verlet method " << endl;
	cout << "Time step = " << delta << endl;
	cout << "Number of steps = " << nstep << endl << endl;
	ReadInput.close();

	//Prepare array for measurements
	iv = 0; //Potential energy
	ik = 1; //Kinetic energy
	ie = 2; //Total energy
	it = 3; //Temperature
	n_props = 4; //Number of observables

	//measurement of g(r)
  	bin_size = (box/2.0)/(double)nbins;

	//QUI DEVO INSERIRE LA SCELTA: E UNA NUOVA RUN O STAI RICOMINCIANDO?
	string N_R;
	cout<<"Insert 'new' if is a new run and 'restart' if you want to restart?"<<endl;
	cin>>N_R;
	cout<<endl<<endl;

	if(N_R=="new"){
		//Read initial configuration
		cout << "Read initial configuration from file config.0 " << endl << endl;
		ReadConf.open("config.0");
		for (int i=0; i<npart; ++i){
			ReadConf >> x[i] >> y[i] >> z[i];
			x[i] = x[i] * box;
			y[i] = y[i] * box;
			z[i] = z[i] * box;
		}
		ReadConf.close();
	//Prepare initial velocities
		cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
		double sumv[3] = {0.0, 0.0, 0.0};
		for (int i=0; i<npart; ++i){
			vx[i] = rand()/double(RAND_MAX) - 0.5;
			vy[i] = rand()/double(RAND_MAX) - 0.5;
			vz[i] = rand()/double(RAND_MAX) - 0.5;

			sumv[0] += vx[i];
			sumv[1] += vy[i];
			sumv[2] += vz[i];
		}
		for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
			double sumv2 = 0.0, fs;
			for (int i=0; i<npart; ++i){
			vx[i] = vx[i] - sumv[0];
			vy[i] = vy[i] - sumv[1];
			vz[i] = vz[i] - sumv[2];
			sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
		}
		sumv2 /= (double)npart;

		fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor 
		for (int i=0; i<npart; ++i){
			vx[i] *= fs;
			vy[i] *= fs;
			vz[i] *= fs;

			xold[i] = Pbc(x[i] - vx[i] * delta);
			yold[i] = Pbc(y[i] - vy[i] * delta);
			zold[i] = Pbc(z[i] - vz[i] * delta);
		}
	}

	else if(N_R=="restart"){
		cout<<"Read initial configuration from file old.final"<<endl;
		ReadConf.open("old.final");
		for(int i=0;i<npart;++i){
			ReadConf>>x[i]>>y[i]>>z[i];
			x[i]=x[i]*box;
			y[i]=y[i]*box;
			z[i]=z[i]*box; 
		}
		ReadConf.close();
		cout<<"Read the T-deltaT configuration from file old.0"<<endl<<endl;
		ReadConfT_deltaT.open("old.0");
		for(int i=0;i<npart;++i){
			ReadConfT_deltaT>>xold[i]>>yold[i]>>zold[i];
			xold[i]=xold[i]*box;
			yold[i]=yold[i]*box;
			zold[i]=zold[i]*box;
		}
		ReadConfT_deltaT.close();
	}
		
	else{
		cerr<<"UNABLE to understand"<<endl;
		terminate();
	}
	return;
}


void Vel_Rescale(void){
	double sumv2=0.0,fs;
	for(int i=0;i<npart;++i){
		vx[i]=(Pbc(x[i]-xold[i]))/delta;
		vy[i]=(Pbc(y[i]-yold[i]))/delta;
		vz[i]=(Pbc(z[i]-zold[i]))/delta;
		sumv2+=vx[i]*vx[i]+vy[i]*vy[i]+vz[i]*vz[i];
	}
	
	sumv2/=(double)npart;
	fs=sqrt(temp*3/sumv2);
	
	for(int i=0;i<npart;++i){
		vx[i]*=fs;
		vy[i]*=fs;
		vz[i]*=fs;

		xold[i]=Pbc(x[i]-vx[i]*delta);
		yold[i]=Pbc(y[i]-vy[i]*delta);
		zold[i]=Pbc(z[i]-vz[i]*delta);
	}
	return;
}



void Move(void){ //Move particles with Verlet algorithm
	double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

	for(int i=0; i<npart; ++i){ //Force acting on particle i
		fx[i] = Force(i,0);
		fy[i] = Force(i,1);
		fz[i] = Force(i,2);
	}

	for(int i=0; i<npart; ++i){ //Verlet integration scheme
		xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
		ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
		znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

		vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
		vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
		vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

		xold[i] = x[i];
		yold[i] = y[i];
		zold[i] = z[i];

		x[i] = xnew;
		y[i] = ynew;
		z[i] = znew;
	}
	return;
}

double Force(int ip, int idir){ //Compute forces as -Grad_ip V(r)
	double f=0.0;
	double dvec[3], dr;

	for (int i=0; i<npart; ++i){
		if(i != ip){
		dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
		dvec[1] = Pbc( y[ip] - y[i] );
		dvec[2] = Pbc( z[ip] - z[i] );

		dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
      	dr = sqrt(dr);

			if(dr < rcut){
				f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
			}
		}
	}
  
	return f;
}

void Measure(){ //Properties measurement
	int bin;
	double v, t, vij, w, wij;
	double dx, dy, dz, dr;
	ofstream Epot, Ekin, Etot, Temp, Pres;

	Epot.open("output_epot.dat",ios::app);
	Ekin.open("output_ekin.dat",ios::app);
	Temp.open("output_temp.dat",ios::app);
	Etot.open("output_etot.dat",ios::app);
	Pres.open("output_etot.dat",ios::app);

	v = 0.0; //reset observables
	w = 0.0;
	t = 0.0;

	//cycle over pairs of particles
	for (int i=0; i<npart-1; ++i){
 		for (int j=i+1; j<npart; ++j){

		dx = Pbc( xold[i] - xold[j] ); // here I use old configurations [old = r(t)]
		dy = Pbc( yold[i] - yold[j] ); // to be compatible with EKin which uses v(t)
		dz = Pbc( zold[i] - zold[j] ); // => EPot should be computed with r(t)

		dr = dx*dx + dy*dy + dz*dz;
		dr = sqrt(dr);
			//update of the histogram of g(r)
			for(int k=0;k<nbins;++k){
        		if(dr>k*bin_size && dr<(k+1)*bin_size) gr[k]+=2;
      		}

			if(dr < rcut){
				vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);
				wij = (48.0/pow(dr,12) - 24.0/pow(dr,6))/3.;
				
				//Potential energy
				v += vij;
				w += wij;

			}
		}          
	}

//Kinetic energy
	for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
   
		stima_pot = v/(double)npart; //Potential energy per particle
		stima_kin = t/(double)npart; //Kinetic energy per particle
		stima_temp = (2.0 / 3.0) * t/(double)npart; //Temperature
		stima_etot = (t+v)/(double)npart; //Total energy per particle
		stima_pres = rho * stima_temp + w/vol;

		Epot << stima_pot  << endl;
		Ekin << stima_kin  << endl;
		Temp << stima_temp << endl;
		Etot << stima_etot << endl;
		Pres << stima_pres << endl;

		Epot.close();
		Ekin.close();
		Temp.close();
		Etot.close();
		Pres.close();
//g(r)
	for (int i=0;i<nbins;++i){
		double dv= 4/3*M_PI * ( pow((2*i+1)*bin_size,3) - pow(i*bin_size,3) );
		stima_gr[i] = gr[i]/rho/m_part/dv;
    }


		return;
}


void ConfFinal(void){ //Write final configuration on config.final and on old.final to restart
	ofstream WriteConf;
	ofstream WriteConfOld;

	cout << "Print final configuration to file config.final and to old.final to restart" << endl << endl;
	WriteConf.open("config.final");
	WriteConfOld.open("old.final");

	for (int i=0; i<npart; ++i){
		WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
		WriteConfOld << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
	}
	WriteConf.close();
	WriteConfOld.close();
	return;
}

void Conf_old0(void){//write the penultimate configuration to restart
	ofstream WriteConfT_deltaT;
	WriteConfT_deltaT.open("old.0");
	for(int i=0;i<npart;++i){
		WriteConfT_deltaT << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
	}
	WriteConfT_deltaT.close();
}

void ConfXYZ(int nconf){ //Write configuration in .xyz format
	ofstream WriteXYZ;

	WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
	WriteXYZ << npart << endl;
	WriteXYZ << "This is only a comment!" << endl;
	for (int i=0; i<npart; ++i){
		WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
	}
	WriteXYZ.close();
}

double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
	return r - box * rint(r/box);
}

double error(double *AV,double *AV2,int n){
	if (n==0) return 0;
	else {
		return sqrt((AV2[n]-pow(AV[n],2))/n);
	}
}

progress_average prog(double *AVE,double *AVE2,int nblocks){
	progress_average ave;

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

void average(void){

	ave_T[nconf/10-1]=sum_T/10.;
	ave_E[nconf/10-1]=sum_E/10.;
	ave_U[nconf/10-1]=sum_U/10.;
	ave_K[nconf/10-1]=sum_K/10.;
	ave_P[nconf/10-1]=sum_P/10.;


	
	ave2_T[nconf/10-1]=pow(ave_T[nconf/10-1],2);
	ave2_E[nconf/10-1]=pow(ave_E[nconf/10-1],2);
	ave2_U[nconf/10-1]=pow(ave_U[nconf/10-1],2);
	ave2_K[nconf/10-1]=pow(ave_K[nconf/10-1],2);
	ave2_P[nconf/10-1]=pow(ave_P[nconf/10-1],2);

	for(int k=0;k<nbins;++k){
		ave_GR[nconf/10-1][k]=sum_GR[k]/10.;
		ave2_GR[nconf/10-1][k]=sum_GR[k]/10.;

	}
	return;
}


void Print_prog_ave(void){
	ofstream AveT_out,AveE_out,AveU_out,AveK_out,AveP_out;
	AveT_out.open("ave_temp.out");
	AveE_out.open("ave_etot.out");
	AveU_out.open("ave_epot.out");
	AveK_out.open("ave_ekin.out");
	AveP_out.open("ave_pres.out");
	// AveGR_out.open("ave_gr.out");
	if(AveT_out.is_open() && AveE_out.is_open() && AveU_out.is_open() && AveK_out.is_open() && AveP_out.is_open()){
		for(int i=0;i<nblocks;++i){
			AveT_out<<Prog_ave_T.sum_prog[i]<<" "<<Prog_ave_T.err_prog[i]<<endl;
			AveE_out<<Prog_ave_E.sum_prog[i]<<" "<<Prog_ave_E.err_prog[i]<<endl;
			AveU_out<<Prog_ave_U.sum_prog[i]<<" "<<Prog_ave_U.err_prog[i]<<endl;
			AveK_out<<Prog_ave_K.sum_prog[i]<<" "<<Prog_ave_K.err_prog[i]<<endl;
			AveP_out<<Prog_ave_P.sum_prog[i]<<" "<<Prog_ave_P.err_prog[i]<<endl;

		}
	} else cout<<"ERROR: Unable to open file"<<endl;

	AveT_out.close();
	AveE_out.close();
	AveU_out.close();
	AveK_out.close();
	AveP_out.close();

	return;
}







/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/