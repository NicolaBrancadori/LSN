import matplotlib.pyplot as plt
import numpy as np

dati=open("risultati.dat","r")
lines=dati.readlines()
Sum=[]
Err=[]
for x in lines:
	i=x.replace('\n',' ') #sostituisco i /n con gli spazi
	Sum.append(float(i.split(' ')[0])) #splitto la riga usando come separatore lo spazio,prendo la prima colonna la leggo come float e la appendo alla lista
	Err.append(float(i.split(' ')[1]))
array_Sum=np.array(Sum) #qui faccio i vettori nunmpy sono più veloci
array_Err=np.array(Err)
array_x=np.arange(100) #creo il vettore x di numeri da 1 a 100

#faccio il plot
array_x*=1000
plt.errorbar(array_x,array_Sum,yerr=array_Err,ecolor='red',color='black') 
plt.title('$\pi$ and $\sigma$ estimations')
plt.xlabel('Lanci')
plt.ylabel('$\pi$')
plt.grid(True)
plt.show()
