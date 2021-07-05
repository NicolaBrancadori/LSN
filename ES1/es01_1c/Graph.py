import numpy as np
import matplotlib.pyplot as plt

dati=open("chi2.dat")
lines=dati.readlines()
vect=[]
for x in lines:
	vect.append(float(x))
y=np.array(vect)
x=np.arange(0,100)
plt.scatter(x,y)
plt.plot([0,100],[100,100],color='red')
plt.ylim(0,200)
plt.ylabel('$\chi^2$')
plt.show()