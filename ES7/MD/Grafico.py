import numpy as np
import matplotlib.pyplot as plt


with open("ave_epot.out") as out:
	dati=np.loadtxt(out)


with open("ave_temp.out") as outT:
	datiT=np.loadtxt(outT)


x=np.arange(dati[:,0].size)

fig=plt.figure(figsize=(8,6))
ax1=fig.add_subplot(2,1,1)
ax2=fig.add_subplot(2,1,2)

ax1.errorbar(x,dati[:,0],yerr=dati[:,1])
ax1.set_title("P")
ax1.grid(True)


ax2.errorbar(x,datiT[:,0],yerr=datiT[:,1])
ax2.set_title("T")
ax2.grid(True)

plt.show()
