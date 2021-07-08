import numpy as np

with open("Temperatura.0") as Temp:
	T=np.loadtxt(Temp,usecols=(0,1),dtype=float)


print("Ho letto il file")
# print("temperatura massima: ",T[:,0].max()," con un deltaL: ",T[:,1].max())