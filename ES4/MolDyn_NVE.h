/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//parameters, observables
const int m_props=4;
int n_props;
int iv,ik,it,ie;
double stima_pot, stima_kin, stima_etot, stima_temp;

// averages
double acc,att;

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];

// thermodynamical state
int npart;
double energy,temp,vol,rho,box,rcut;

// simulation
int istep, nstep, iprint, seed;
double delta;
int nconf=1;


//blocks
const int nblocks=100;
struct progress_average{
	double sum_prog[nblocks]={0};
	double sum2_prog[nblocks]={0};
	double err_prog[nblocks]={0};
};
progress_average Prog_ave_T,Prog_ave_E,Prog_ave_U,Prog_ave_K;
double sum_T=0., sum_E=0., sum_U=0., sum_K=0.;
double ave_T[nblocks], ave_E[nblocks], ave_U[nblocks], ave_K[nblocks];
double ave2_T[nblocks], ave2_E[nblocks], ave2_U[nblocks], ave2_K[nblocks];


//functions
void Input(void);
void Vel_Rescale(void);
void Move(void);
void ConfFinal(void);
void ConfXYZ(int);
void Measure(void);
void Conf_old0(void);
double Force(int, int);
double Pbc(double);
double error(double *, double *,int );
void average(void);
progress_average prog(double *, double *, int);
void Print_prog_ave(void);

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
