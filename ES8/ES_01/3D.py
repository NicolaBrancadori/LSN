import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

with open("MuSigma.dat") as MuSigma:
	MS=np.loadtxt(MuSigma,usecols=(0,1,2),dtype=float)

# print(MS)
# print(np.where(MS[:,0]==MS[:,0].min()))
a=np.where(MS[:,0]==MS[:,0].min())[0][0]


print("Valore di energia minimo:", MS[a,0])
print("μ:", MS[a,1])
print("σ:", MS[a,2])

fig=plt.figure(figsize=(10,6))
ax=Axes3D(fig)
ax.scatter(MS[:,1],MS[:,2],MS[:,0],marker='.')

ax.set_xlabel('l')
ax.set_ylabel('s')
ax.set_zlabel('H')

ax.legend()

plt.show()

