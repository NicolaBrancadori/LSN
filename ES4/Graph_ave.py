import numpy as np
import matplotlib.pyplot as plt

with open("ave_temp.out") as ave_temp:#mentre il file è aperto (dopo viene automaticamente chiuso)
	ave_T=np.loadtxt(ave_temp,usecols=(0,1),dtype=float)#leggo i dati e li metto in un np.array

with open("ave_etot.out") as ave_etot:
	ave_E=np.loadtxt(ave_etot,usecols=(0,1),dtype=float)

with open("ave_epot.out") as ave_epot:
	ave_U=np.loadtxt(ave_epot,usecols=(0,1),dtype=float)

with open("ave_ekin.out") as ave_ekin:
	ave_K=np.loadtxt(ave_ekin,usecols=(0,1),dtype=float)	


x=np.arange(100)#array delle x da 0 a 1000

fig=plt.figure(figsize=(10,7))

ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)
# ax5=fig.add_subplot(2,2,5)


ax1.errorbar(x,ave_T[:,0],yerr=ave_T[:,1],label='ave_Temp')
ax2.errorbar(x,ave_E[:,0],yerr=ave_E[:,1],label='ave_Etot')
ax3.errorbar(x,ave_U[:,0],yerr=ave_U[:,1],label='ave_Epot')
ax4.errorbar(x,ave_K[:,0],yerr=ave_K[:,1],label='ave_Ekin')
# ax5.plot(x,ave_T[:,0],label='ave_Temp')
# ax5.plot(ave_E[:,0],label='ave_Etot')
# ax5.plot(ave_U[:,0],label='ave_Epot')
# ax5.plot(ave_K[:,0],label='ave_Ekin')

ax1.legend()
ax2.legend()
ax3.legend()
ax4.legend()
# ax5.legend()

plt.show()
