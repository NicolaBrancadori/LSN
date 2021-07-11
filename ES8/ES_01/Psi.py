import numpy as np
import matplotlib.pyplot as plt


def Vpot(x):
    return (x**2 - 2.5)*x**2
    #return 0.5*x**2

File=open("Psi.dat")
PsiMes=np.array(File.readlines(),dtype=float)
XPsiMes=np.arange(0,PsiMes.size)


hbar = 1
m = 1
a = 10
N = 1000 # number of iterations

# Step sizes
x = np.linspace(-a/2, a/2, N)
dx = x[1] - x[0] # the step size
V = Vpot(x)

# The central differences method: f" = (f_1 - 2*f_0 + f_-1)/dx^2

CDiff = np.diag(np.ones(N-1),-1)-2*np.diag(np.ones(N),0)+np.diag(np.ones(N-1),1)
# np.diag(np.array,k) construct a "diagonal" matrix using the np.array
# The default is k=0. Use k>0 for diagonals above the main diagonal, 
# and k<0 for diagonals below the main diagonal

# Hamiltonian matrix
H = (-(hbar**2)*CDiff)/(2*m*dx**2) + np.diag(V)

# Compute eigenvectors and their eigenvalues
E,psi = np.linalg.eigh(H)

# Take the transpose & normalize
psi = np.transpose(psi)
psi = psi/np.sqrt(dx)

print("Ground state energy: ", E[0])
print("1st excited state energy: ", E[1])
print("2nd excited state energy: ", E[2])

# print(np.linspace(-2,2,endpoint=False),len(np.linspace(-2,2,endpoint=False)))
isto_y,isto_x=np.histogram(PsiMes,bins=np.linspace(-3,3,num=400),density=True)
# isto_y=isto_y/isto_y.sum()
isto_x=np.delete(isto_x,399)



# Plot a few things
plt.figure(figsize=(8,5))
scale = 0.3
# plt.plot(x, scale*V, color="Black", label="Potential") # plot the potential
plt.plot(x,(psi[0])**2,label='Ground state')
# plt.plot(x,(psi[1])**2)
# plt.plot(x,(psi[2])**2)
plt.plot(isto_x,isto_y)
plt.title("Potential & Probabilities")
plt.legend()
# plt.xlabel("x")
plt.grid(True)
plt.xlim((-3,3))
# plt.ylim((-0.6,0.6))
plt.show()




