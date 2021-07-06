import numpy as np
import matplotlib.pyplot as plt

Dati_CD=open("Call_direct.dat","r")
Dati_Cd=open("Call_discr.dat","r")
Dati_PD=open("Put_discr.dat","r")
Dati_Pd=open("Put_direct.dat","r")

lines_CD=Dati_CD.readlines()
lines_Cd=Dati_Cd.readlines()
lines_PD=Dati_PD.readlines()
lines_Pd=Dati_Pd.readlines()

#Creo liste vuote dove metto i dati
CD_price=[]
err_CD=[]
Cd_price=[]
err_Cd=[]
PD_price=[]
err_PD=[]
Pd_price=[]
err_Pd=[]

for x in lines_CD:
	i=x.replace('\n',' ')
	CD_price.append(float(i.split(' ')[0]))
	err_CD.append(float(i.split(' ')[1]))
for x in lines_Cd:
	i=x.replace('\n',' ')
	Cd_price.append(float(i.split(' ')[0]))
	err_Cd.append(float(i.split(' ')[1]))
for x in lines_PD:
	i=x.replace('\n',' ')
	PD_price.append(float(i.split(' ')[0]))
	err_PD.append(float(i.split(' ')[1]))
for x in lines_Pd:
	i=x.replace('\n',' ')
	Pd_price.append(float(i.split(' ')[0]))
	err_Pd.append(float(i.split(' ')[1]))

#qui creo il vettore x 
x=list(range(0,100))
V_x=np.array(x)
V_x*=10000

#qui creo i vettori numpy con le liste di prima. Sono più facilmente maneggiabili
V_CD_price=np.array(CD_price)
V_err_CD=np.array(err_CD)
V_Cd_price=np.array(Cd_price)
V_err_Cd=np.array(err_Cd)
V_PD_price=np.array(PD_price)
V_err_PD=np.array(err_PD)
V_Pd_price=np.array(Pd_price)
V_err_Pd=np.array(err_Pd)



#plot

fig=plt.figure(figsize=(9,6.5))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)

ax1.errorbar(V_x,V_CD_price-14.98,yerr=V_err_CD,elinewidth=1)
ax2.errorbar(V_x,V_Cd_price-14.98,yerr=V_err_Cd,elinewidth=1)
ax3.errorbar(V_x,V_PD_price-5.46,yerr=V_err_PD,elinewidth=1)
ax4.errorbar(V_x,V_Pd_price-5.46,yerr=V_err_Pd,elinewidth=1)

#griglia
ax1.grid(True)
ax2.grid(True)
ax3.grid(True)
ax4.grid(True)

#titolo assi
ax1.set_title('Call direct',fontsize=12)
ax2.set_title('Call discretized',fontsize=12)
ax3.set_title('Put direct',fontsize=12)
ax4.set_title('Put discretized',fontsize=12)

#etichette assi
ax1.set_ylabel(r'$\langle e^{-rt}(S(T)-K)^+ \rangle-14.98$',fontsize=10)
ax3.set_ylabel(r'$\langle e^{-rt}(S(T)-K)^+ \rangle-5.46$',fontsize=10)
ax3.set_xlabel('Number of S(T) simulated',fontsize=10)
ax4.set_xlabel('Number of S(T) simulated',fontsize=10)

#dimensione dei tick degli assi
ax1.tick_params(labelsize=8)
ax2.tick_params(labelsize=8)
ax3.tick_params(labelsize=8)
ax4.tick_params(labelsize=8)



# ax1.axhline(y=14.98,linestyle='--',c='red') how to create an otizontal line
# ax1.text(880000,14.93,'14.98',c='red') how to insert a text in a graphic

plt.show()




