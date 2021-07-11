import numpy as np
import matplotlib.pyplot as plt
import math

with open("output.pres.0") as pres:
	P=np.loadtxt(pres,usecols=(0,1,2,3),dtype=float)
P_True=P[1000:,1]

with open("output.epot.0") as epot:
	U=np.loadtxt(epot,usecols=(0,1,2,3),dtype=float)
U_True=U[1000:,1]


def error(AV,AV2,n):
	prog = AV.sum()/n
	prog2 = AV2.sum()/n
	if n==0: 
		return 0
	
	else:
		return math.sqrt((prog2-prog**2)/float(n))

#I due vettori con i dati istantanei sono P_True e U_True
k=20
N=10000
M=100000


with open("medie.blocks.0",'w') as Medie:

	while(k<=N):
		
		ave=np.zeros(k)
		ave2=np.zeros(k)
		
		for i in range(k):
			Sum=0
			
			for j in range(int(i*M/k), int(M/k + i*M/k)):
				Sum+=P_True[j]

			ave[i]=Sum/float(M/k)
			ave2[i]=ave[i]**2
		sum_ave = ave.sum()/k
		sum_ave2 = ave2.sum()/k

		#print(ave," ", ave2)
		err=np.sqrt((sum_ave2 - sum_ave**2)/k)
		
		print(ave[k-1],' ',err,' ',M/k, file=Medie)
		
		while(1<2):
			k+=1
			if(M%k==0):
				#print(k)
				break
Medie.close()

	













