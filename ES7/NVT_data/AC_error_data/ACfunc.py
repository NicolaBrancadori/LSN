import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


#Ho equilibrato il sistema con 10mila passi e ho stampato i valori istantanei di P e U/N.
#Ho calcolato le funzioni di autocorrelazione.
#Ho fittato tali funzioni con un esponenziale exp(-t/tau)
#Ho ottenuto per P:tau=8.74800658  e per U/N:tau=8.86308951.


def funcExp(x,a):
	return np.exp(-x/a)


with open("output.pres.0") as pres:
	P=np.loadtxt(pres,usecols=(0,1,2,3),dtype=float)
P_True=P[1000:,1]

with open("output.epot.0") as epot:
	U=np.loadtxt(epot,usecols=(0,1,2,3),dtype=float)
U_True=U[1000:,1]

N_media=90000

print("\n","Misuro la funzione di AC per la pressione")
lista_P=[]
sigma=(P_True[:N_media]**2).sum()/(N_media) - (P_True[:N_media].sum()/(N_media))**2
for tau in range(50):
	
	sum1=0
	sum2=0
	sum3=0
	
	for i in range(0,N_media):

		sum1+=P_True[i]*P_True[i+tau]
		sum2+=P_True[i]
		sum3+=P_True[i+tau]
	
	sum1/=(N_media)
	sum2/=(N_media)
	sum3/=(N_media)

	lista_P.append((sum1-sum2*sum3)/sigma)


print("\n","Misuro la funzione di AC per l'energia")
lista_U=[]
sigma=(U_True[:N_media]**2).sum()/(N_media) - (U_True[:N_media].sum()/(N_media))**2

for tau in range(50):

	sum1=0
	sum2=0
	sum3=0
	
	for i in range(0,N_media):
		
		sum1+=U_True[i]*U_True[i+tau]
		sum2+=U_True[i]
		sum3+=U_True[i+tau]
	
	sum1/=(N_media)
	sum2/=(N_media)
	sum3/=(N_media)

	lista_U.append((sum1-sum2*sum3)/sigma)


AC_U=np.array(lista_U)
x_dataU=np.arange(1,tau+2)

AC_P=np.array(lista_P)
x_dataP=np.arange(1,tau+2)


parExpP,covExpP=curve_fit(funcExp,x_dataP,AC_P)
y_fitExpP=funcExp(x_dataP,parExpP)


parExpU,covExpU=curve_fit(funcExp,x_dataU,AC_U)
y_fitExpU=funcExp(x_dataU,parExpU)


print('\n\n','tau pressione: ', parExpP)
print('\n\n','tau Energia potenziale: ', parExpU)

fig=plt.figure(figsize=(10,6))

ax1=fig.add_subplot(2,1,1)
ax2=fig.add_subplot(2,1,2)

ax1.set_title('pressione')
ax1.plot(x_dataP,y_fitExpP,label='fit_exp')
ax1.scatter(x_dataP,AC_P,label='data',marker='.')
ax1.legend()

ax2.set_title('energia potenziale')
ax2.plot(x_dataU,y_fitExpU,label='fit_exp')
ax2.scatter(x_dataU,AC_U,label='data',marker='.')
ax2.legend()
ax2.set_ylim(-2,+2)



plt.show()



