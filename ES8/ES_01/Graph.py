import numpy as np
import matplotlib.pyplot as plt


with open("Hamiltonian.dat") as Ham:
	H=np.loadtxt(Ham,usecols=(0,1),dtype=float)
print(H[H[:,0].size-1,0])

x=np.arange(0,H[:,0].size)

plt.errorbar(x,H[:,0],yerr=H[:,1])

plt.show()