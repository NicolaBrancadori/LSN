import numpy as np
import matplotlib.pyplot as plt

with open("gv/output.gave.liquid") as out:
	dati=np.loadtxt(out)

x=np.arange(dati[:,0].size)
plt.errorbar(x,dati[:,0],yerr=dati[:,1])
plt.show()