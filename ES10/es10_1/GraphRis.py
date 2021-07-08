import numpy as np
import matplotlib.pyplot as plt

with open("Risultati.0") as Ris:
	y=np.loadtxt(Ris,dtype=float)

x=np.arange(y.size)

plt.plot(x,y)
plt.show()