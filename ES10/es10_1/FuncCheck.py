import numpy as np
from numpy import random as rnd
import math
from itertools import permutations
import matplotlib.pyplot as plt


def CalL(vec):
	S=0
	
	for i in range(0,vec[:,0].size-1):
		S+=math.sqrt( (vec[i][0]-vec[i+1][0])**2 + (vec[i][1]-vec[i+1][1])**2 )

	S+= math.sqrt( (vec[0][0]-vec[vec[:,0].size-1][0])**2 + (vec[0][1]-vec[vec[:,0].size-1][1])**2 )

	return S

def Sort_Acc(SortArr,Arr):
    for i in range(0,SortArr[:,0].size):
        for j in range(0,Arr.size):
            if(SortArr[i,2]==Arr[j]):
                a=SortArr[i,0]
                b=SortArr[i,1]
                c=SortArr[i,2]
                SortArr[i,0]=SortArr[j,0]
                SortArr[i,1]=SortArr[j,1]
                SortArr[i,2]=SortArr[j,2]
                SortArr[j,0]=a
                SortArr[j,1]=b
                SortArr[j,2]=c
    return SortArr

#Vettore citta
with open('citta.0') as cit:
    x=np.loadtxt(cit,usecols=(0,1,2),dtype=float)





perm=permutations(x[1:,2])
# m=1
# for i in perm:
#     m+=1
# print(m)


l=np.empty((362880,11))
c=0
for t in perm:
    if(c%100000==0):
        print(c)
    a=np.insert(np.array(t),0,x[0,2],axis=0)
    L=Sort_Acc(x,a)
    S1=CalL(L)
    l[c][0]=S1
    l[c][1:]=L[:,2]
    c+=1
print("eccolo:\n")
print(l[np.argmin(l[:,0]),:] ," cio: ",np.argmin(l[:,0]))



#Best Path 10 citta
# [ 5.89583658  1.          5.          6.          4.          2.        8.         10.          7.          3.          9.        ]





