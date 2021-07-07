import numpy as np
import matplotlib.pyplot as plt

with open("Uniforme_1.dat") as Unif_1:
	R1_Unif=np.loadtxt(Unif_1,usecols=(0,1),dtype=float)

with open("Uniforme_2.dat") as Unif_2:
	R2_Unif=np.loadtxt(Unif_2,usecols=(0,1),dtype=float)

with open("Gauss_1.dat") as Gauss_1:
	R1_Gauss=np.loadtxt(Gauss_1,usecols=(0,1),dtype=float)

with open("Gauss_2.dat") as Gauss_2:
	R2_Gauss=np.loadtxt(Gauss_2,usecols=(0,1),dtype=float)


x=np.arange(0,R1_Unif[:,0].size)

fig=plt.figure(figsize=(12,6))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)

ax1.errorbar(x,R1_Unif[:,0],yerr=R1_Unif[:,1],label='GS Uniform') #,elinewidth=0.2)
ax2.errorbar(x,R2_Unif[:,0],yerr=R2_Unif[:,1],label='1ES Uniform') #,elinewidth=0.2)
ax3.errorbar(x,R1_Gauss[:,0],yerr=R1_Gauss[:,1],label='GS Gauss') #,elinewidth=0.2)
ax4.errorbar(x,R2_Gauss[:,0],yerr=R2_Gauss[:,1],label='1ES Gauss') #,elinewidth=0.2)

ax1.set_ylim(1.475,1.525)
ax2.set_ylim(4.97,5.05)
ax3.set_ylim(1.475,1.525)
ax4.set_ylim(4.97,5.05)

# ax1.set_xlim(-20,600)
# ax2.set_xlim(-20,600)
# ax3.set_xlim(-20,600)
# ax4.set_xlim(-20,600)

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()

ax1.axhline(y=1.5,c='darkblue',linewidth=0.8)
ax3.axhline(y=1.5,c='darkblue',linewidth=0.8)

ax2.axhline(y=5,c='darkblue',linewidth=0.8)
ax4.axhline(y=5,c='darkblue',linewidth=0.8)


plt.show()




