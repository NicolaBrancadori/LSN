import numpy as np
import matplotlib.pyplot as plt

with open("NumberOfCorrStep_U1.dat") as Nsteps_U1:
	Steps_U1=np.loadtxt(Nsteps_U1,usecols=(0),dtype=int)

with open("NumberOfCorrStep_U2.dat") as Nsteps_U2:
	Steps_U2=np.loadtxt(Nsteps_U2,usecols=(0),dtype=int)

with open("NumberOfCorrStep_G1.dat") as Nsteps_G1:
	Steps_G1=np.loadtxt(Nsteps_G1,usecols=(0),dtype=int)

with open("NumberOfCorrStep_G2.dat") as Nsteps_G2:
	Steps_G2=np.loadtxt(Nsteps_G2,usecols=(0),dtype=int)



fig=plt.figure(figsize=(10,6))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)

ax1.hist(Steps_U1,bins=np.linspace(0,max(Steps_U1)),label='GS Uniform')
ax2.hist(Steps_U2,bins=np.linspace(0,max(Steps_U2)),label='ES Uniform')
ax3.hist(Steps_G1,bins=np.linspace(0,max(Steps_G1)),label='GS Gauss')
ax4.hist(Steps_G2,bins=np.linspace(0,max(Steps_G2)),label='ES Gauss')

ax3.set_xlabel("steps per scollerarsi")
ax4.set_xlabel("steps per scollerarsi")

ax1.set_ylabel("conteggio misure")
ax3.set_ylabel("conteggio misure")

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()

plt.show()


