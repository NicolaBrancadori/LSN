import numpy as np
import matplotlib.pyplot as plt

with open("EqCheck_U1.dat") as Unif_1:
	U1=np.loadtxt(Unif_1,usecols=(0,1),dtype=float)

with open("EqCheck_U2.dat") as Unif_2:
	U2=np.loadtxt(Unif_2,usecols=(0,1),dtype=float)

with open("EqCheck_G1.dat") as Gauss_1:
	G1=np.loadtxt(Gauss_1,usecols=(0,1),dtype=float)

with open("EqCheck_G2.dat") as Gauss_2:
	G2=np.loadtxt(Gauss_2,usecols=(0,1),dtype=float)


x1=np.arange(0,U1[:,0].size)
x2=np.arange(0,U2[:,0].size)
x3=np.arange(0,G1[:,0].size)
x4=np.arange(0,G2[:,0].size)

fig=plt.figure(figsize=(12,6))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)

ax1.errorbar(x1,U1[:,0],yerr=U1[:,1],label='GS Uniform')
ax2.errorbar(x2,U2[:,0],yerr=U2[:,1],label='1ES Uniform')
ax3.errorbar(x3,G1[:,0],yerr=G1[:,1],label='GS Gauss')
ax4.errorbar(x4,G2[:,0],yerr=G2[:,1],label='1ES Gauss')

# ax1.set_ylim(1.46,1.60)
# ax2.set_ylim(4.96,5.10)
# ax3.set_ylim(1.46,1.60)
# ax4.set_ylim(4.96,5.10)

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




