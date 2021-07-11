import numpy as np
import matplotlib.pyplot as plt

with open("medie.blocks.0") as Media:
	M=np.loadtxt(Media,usecols=(0,1,2),dtype=float)



ind=M[:,2].argsort()
M=M[ind]
#plt.errorbar(x,M[:,0],yerr=M[:,1])
plt.plot(M[:,2],M[:,1])
plt.show()
