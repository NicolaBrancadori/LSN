import numpy as np
import matplotlib.pyplot as plt

with open("MigliorPercorso.dat") as BestPath:
	BP=np.loadtxt(BestPath,usecols=(0,1,2),dtype=float)



plt.plot(BP[:,0],BP[:,1])
plt.show()