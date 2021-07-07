import numpy as np
import matplotlib.pyplot as plt


with open("output.ene.0") as Ene:
	E=np.loadtxt(Ene,usecols=(0,1,2,3),dtype=float)

# with open("output.Chi.0") as Chi:
# 	C=np.loadtxt(Chi,usecols=(2,3),dtype=float)
# C_true=np.empty((20,0),float)


# with open("input.dat") as File_input:
# 	Input=np.loadtxt(File_input,max_rows=1,dtype=float)

# print(Input)
# Temp=np.append(Input,Input[0])
# print(Temp)


x=np.arange(E[:,0].size)

plt.errorbar(x,E[:,2],yerr=E[:,3])

#plt.ylim(-0.5848,-0.5813)
#plt.plot(x,E[:,1])
plt.show()