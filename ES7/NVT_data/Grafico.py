import numpy as np
import matplotlib.pyplot as plt


with open("output.epot.solid") as out:
	dati= np.loadtxt(out)

x=np.arange(dati[:,0].size)

plt.errorbar(x,dati[:,2],yerr=dati[:,3])
plt.show()