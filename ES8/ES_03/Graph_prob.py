import numpy as np
import matplotlib.pyplot as plt


with open("probability.dat") as Pout:
	P=np.loadtxt(Pout)
print(P[:,1])
plt.errorbar(P[:,0],P[:,1],yerr=P[:,2])

plt.show()