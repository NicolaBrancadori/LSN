import numpy as np
import matplotlib.pyplot as plt

with open("output_etot.dat") as E_output:#mentre il file è aperto (dopo viene automaticamente chiuso)
	E=np.array(E_output.readlines(),dtype=float)#leggo i dati linea per linea li converto in float e li metto in un np.array

with open("output_ekin.dat") as K_output:
	K=np.array(K_output.readlines(),dtype=float)

with open("output_epot.dat") as U_output:
	U=np.array(U_output.readlines(),dtype=float)

with open("output_temp.dat") as T_output:
	T=np.array(T_output.readlines(),dtype=float)	

# with open("output_temp_NOOPT.dat") as T_NOOPT_output:
# 	T_NOOPT=np.array(T_NOOPT_output.readlines(),dtype=float)	

# with open("ave_temp.out") as ave_temp:
	# T_ave=np.array(ave_temp.readlines(),dtype=float)	

x=np.arange(1000)#array delle x da 0 a 1000
x_ave=np.arange(100)
y=np.ones(1000)
y*=0.8
#plottare tutto nello stesso grafico
plt.plot(x,T,label='Temp')
# plt.plot(x,T_NOOPT,label='Temp_NOOPT')
plt.plot(x,E,label='E_tot')
plt.plot(x,U,label='E_pot')
plt.plot(x,K,label='E_kin')
# plt.plot(x_ave,T_ave)
# plt.plot(x,y)
plt.legend()
plt.show()


#Plottare in diversi grafici nella stessa figura
"""
fig=plt.figure(figsize=(6,6))
ax1=fig.add_subplot(2,1,1)
ax2=fig.add_subplot(2,1,2)
ax1.plot(x,E,label='E_kin')
ax2.plot(x,U,label='E_pot')
ax1.legend()
ax2.legend()
"""
