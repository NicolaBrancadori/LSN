import numpy as np
import matplotlib.pyplot as plt

with open("U1_near.dat") as U1_near:
	R_U1_near=np.loadtxt(U1_near,usecols=(0,1),dtype=float)

with open("U1_far.dat") as U1_far:
	R_U1_far=np.loadtxt(U1_far,usecols=(0,1),dtype=float)

x=np.arange(0,R_U1_near[:,0].size)
x*=100
fig=plt.figure(figsize=(10,6))


ax1=fig.add_subplot(2,1,1)
ax2=fig.add_subplot(2,1,2)


ax1.errorbar(x,R_U1_near[:,0],yerr=R_U1_near[:,1],label='Groun state near',elinewidth=1)
ax2.errorbar(x,R_U1_far[:,0],yerr=R_U1_far[:,1],label='Ground state far',elinewidth=1)

ax1.set_ylim(1.2,2.1)
ax2.set_ylim(1.2,2.1)

ax1.legend()
ax2.legend()

ax1.axhline(y=1.5,c='darkblue',linewidth=0.8)
ax2.axhline(y=1.5,c='darkblue',linewidth=0.8)

plt.show()