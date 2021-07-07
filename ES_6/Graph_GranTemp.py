import numpy as np
import matplotlib.pyplot as plt

#input data
points=100
T = np.linspace(0.2,3.0,num=points)
beta = 1/T
J = 1.0
Ns = 50
h=0.02 #external field

#just some variables for the counts
th = np.tanh(J/T)
thN= th**Ns
ch = 1/th

#energy
e = -J*( th + ch*thN )/( 1 + thN )


#Heat capacity
heat=((beta*J)**2)*(((1+thN+(Ns-1)*(th**2)+(Ns-1)*(ch**2)*thN)/(1+thN))-Ns*((th+ch*thN)/(1+thN))**2)

#Magnetization
l1 = np.exp(beta*J)*np.cosh(beta*h)+np.sqrt(np.exp(2*beta*J)*np.cosh(beta*h)*np.cosh(beta*h)-2*np.sinh(2*beta*J))
l2 = np.exp(beta*J)*np.cosh(beta*h)-np.sqrt(np.exp(2*beta*J)*np.cosh(beta*h)*np.cosh(beta*h)-2*np.sinh(2*beta*J))
Z = l1**Ns + l2**Ns
M = (np.exp(beta*J)*np.sinh(beta*h)*((l1**(Ns-1))*(1+np.exp(beta*J)*np.cosh(beta*h)/np.sqrt(np.exp(2*beta*J)*np.cosh(beta*h)*np.cosh(beta*h)-2*np.sinh(2*beta*J))) 
        + (l2**(Ns-1))*(1-np.exp(beta*J)*np.cosh(beta*h)/np.sqrt(np.exp(2*beta*J)*np.cosh(beta*h)*np.cosh(beta*h)-2*np.sinh(2*beta*J)))))/(Z)

#Susceptibility
X = beta*np.exp(2*beta*J)*(1-thN)/(1+thN)


with open("SuscettivitàMagnetica_Metropolis.dat") as FileFin_Chi_Met:
	Chi_Met=np.loadtxt(FileFin_Chi_Met,usecols=(0,1,2),dtype=float)

with open("EnergiaInterna_Metropolis.dat") as FileFin_Ene_Met:
	Ene_Met=np.loadtxt(FileFin_Ene_Met,usecols=(0,1,2),dtype=float)

with open("CapacitàTermica_Metropolis.dat") as FileFin_Heat_Met:
	Heat_Met=np.loadtxt(FileFin_Heat_Met,usecols=(0,1,2),dtype=float)

with open("Magnetizzazione_Metropolis.dat") as FileFin_Mag_Met:
	Mag_Met=np.loadtxt(FileFin_Mag_Met,usecols=(0,1,2),dtype=float)



with open("SuscettivitàMagnetica_Gibbs.dat") as FileFin_Chi_Gib:
	Chi_Gib=np.loadtxt(FileFin_Chi_Gib,usecols=(0,1,2),dtype=float)

with open("EnergiaInterna_Gibbs.dat") as FileFin_Ene_Gib:
	Ene_Gib=np.loadtxt(FileFin_Ene_Gib,usecols=(0,1,2),dtype=float)

with open("CapacitàTermica_Gibbs.dat") as FileFin_Heat_Gib:
	Heat_Gib=np.loadtxt(FileFin_Heat_Gib,usecols=(0,1,2),dtype=float)

with open("Magnetizzazione_Gibbs.dat") as FileFin_Mag_Gib:
	Mag_Gib=np.loadtxt(FileFin_Mag_Gib,usecols=(0,1,2),dtype=float)


#Sorting per il plot, but i did a scatter so it's useless.
X_Met=Chi_Met[Chi_Met[:,0].argsort()]
E_Met=Ene_Met[Ene_Met[:,0].argsort()]
C_Met=Heat_Met[Heat_Met[:,0].argsort()]
M_Met=Mag_Met[Mag_Met[:,0].argsort()]


X_Gib=Chi_Gib[Chi_Gib[:,0].argsort()]
E_Gib=Ene_Gib[Ene_Gib[:,0].argsort()]
C_Gib=Heat_Gib[Heat_Gib[:,0].argsort()]
M_Gib=Mag_Gib[Mag_Gib[:,0].argsort()]




#PLOT
fig=plt.figure(figsize=(10,6))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)



ax2.plot(T,e,label='H_expected',ls='solid',linewidth=1.2,color='red')
ax3.plot(T,heat,label='C_expected',ls='solid',linewidth=1.2,color='red')
ax1.plot(T,X,label='X_expected',ls='solid',linewidth=1.2,color='red')
ax4.plot(T,M,label='M_expected',ls='solid',linewidth=1.2,color='red')

ax1.scatter(X_Met[:,0],X_Met[:,1],label='X_Met',marker='o',s=30,c='darkblue')
ax2.scatter(E_Met[:,0],E_Met[:,1],label='H_Met',marker='o',s=30,c='darkblue')
ax3.scatter(C_Met[:,0],C_Met[:,1],label='C_Met',marker='o',s=30,c='darkblue')
ax4.scatter(M_Met[:,0],M_Met[:,1],label='M_Met',marker='o',s=30,c='darkblue')

ax1.scatter(X_Gib[:,0],X_Gib[:,1],label='X_Gib',marker='v',s=20,c='deepskyblue')
ax2.scatter(E_Gib[:,0],E_Gib[:,1],label='H_Gib',marker='v',s=20,c='deepskyblue')
ax3.scatter(C_Gib[:,0],C_Gib[:,1],label='C_Gib',marker='v',s=20,c='deepskyblue')
ax4.scatter(M_Gib[:,0],M_Gib[:,1],label='M_Gib',marker='v',s=20,c='deepskyblue')


ax3.set_xlabel("T")
ax4.set_xlabel("T")

ax1.set_ylabel(r'$\chi/N$')
ax2.set_ylabel('U/N')
ax3.set_ylabel('C/N')
ax4.set_ylabel('M/N')

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()


plt.show()



