import numpy as np
import matplotlib.pyplot as plt

dati=open("gauss.dat")
lines=dati.readlines()
Exp_1=[]
Exp_2=[]
Exp_10=[]
Exp_100=[]
for x in lines:
	i=x.replace('\n',' ')
	Exp_1.append(float(i.split(' ')[0]))
	Exp_2.append(float(i.split(' ')[1]))
	Exp_10.append(float(i.split(' ')[2]))
	Exp_100.append(float(i.split(' ')[3]))

x_1=np.array(Exp_1)
x_2=np.array(Exp_2)
x_10=np.array(Exp_10)
x_100=np.array(Exp_100)

fig=plt.figure(figsize=(9,6.5))
fig.suptitle('Histograms of $10^4$ $S_N= 1/N \sum_i^N x_i$, where $x_i$ are random variables obtained throwing a standard dice',fontsize=11)
ax1=fig.add_subplot(2,2,1)
ax2=fig.add_subplot(2,2,2)
ax3=fig.add_subplot(2,2,3)
ax4=fig.add_subplot(2,2,4)
# bins=np.linspace(0,6,100)
ax1.hist(x_1,bins=np.linspace(-5,5,100))
ax2.hist(x_2,bins=np.linspace(-5,5,100))
ax3.hist(x_10,bins=np.linspace(-5,5,100))
ax4.hist(x_100,bins=np.linspace(-5,5,100))

ax1.set_title('N=1')
ax1.set_ylabel('counts')

ax2.set_title('N=2')


ax3.set_title('N=10')
ax3.set_ylabel('counts')
ax3.set_xlabel('$x_i$')

ax4.set_title('N=100')
ax4.set_xlabel('$x_i$')

plt.show()
