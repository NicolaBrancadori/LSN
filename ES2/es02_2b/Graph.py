import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit 

def func(x,k):
	return k*np.sqrt(x)


dati=open("Risultati.dat","r")
lines=dati.readlines()
r=[]
err=[]
for x in lines:
	i=x.replace('\n',' ') #sostituisco i /n con gli spazi
	r.append(float(i.split(' ')[0])) #splitto la riga usando come separatore lo spazio,prendo la prima colonna la leggo come float e la appendo alla lista
	err.append(float(i.split(' ')[1]))
array_r=np.array(r) #qui faccio i vettori nunmpy sono più veloci
array_err=np.array(err)
array_x=np.arange(100) #creo il vettore x di numeri da 1 a 100

k_opt=curve_fit(func,array_x,array_r) #questo è il fit
y_fit=func(array_x,k_opt[0])
print(k_opt[0])
# faccio il plot
array_x*=100
plt.errorbar(array_x,array_r,yerr=array_err,color='darkolivegreen',ecolor='blueviolet',fmt='o',markersize=3) 
plt.plot(array_x,y_fit,c='black')
plt.xlabel('Steps')
plt.ylabel('$\sqrt{|r_N|^2}$')
plt.grid(True)
plt.show()
