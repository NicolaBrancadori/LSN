import numpy as np
import matplotlib.pyplot as plt


with open("kinetic.dat") as Kout:
	K=np.loadtxt(Kout)

with open("potential.dat") as Uout:
	U=np.loadtxt(Uout)

H=np.zeros( (K[:,0].size,3)  )

y=np.ones(H[:,0].size)
y*=-0.46

H[:,0]=K[:,0]
H[:,1]=K[:,1]+U[:,1]
H[:,2]=np.sqrt(pow(K[:,2],2)+pow(U[:,2],2))
# print(H)
plt.errorbar(K[:,0],K[:,1],yerr=K[:,2],label='K')
# plt.plot(K[:,0],K[:,1])
plt.errorbar(U[:,0],U[:,1],yerr=U[:,2],label='U')
plt.errorbar(H[:,0],H[:,1],yerr=H[:,2],label='H',elinewidth=0.5)
plt.plot(H[:,0],y)
plt.legend()
plt.show()