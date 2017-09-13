from sys import argv
import numpy as np
import matplotlib.pyplot as plt

file = open(argv[3], 'r') #vary between 1-3 to alternate which text file from which algorithm to use
n = int(file.readline())
n+= 1
f = np.zeros(n+1)
u = np.zeros(n+1)
x = np.linspace(0, 1, n+1)

with file as filename:
    lines = [line.split() for line in filename]
print lines
for k in range(len(lines)): #read data into array
    u[k] = float(lines[k][0]) #0 for the LU comp and 1 for the others
    #u[k] = float(lines[k][1])
file.close()
f_t = 100*np.exp(-10*x)/n**2
u_t = 1 - (1-np.exp(-10))*x-np.exp(-10*x) #exact solution

rel_error = []
for k in range(n):
    if u_t[k] != 0:
        rel_error.append(np.log10(np.abs((u[k]-u_t[k])/u_t[k])))
#print max(rel_error) #used to find max_error
h_err = []
for k in range(1, 8):
    h_err.append(10**-k)
#max_err = [3.05*10**-1, 0.017, 1.6*10**-3, 1.64*10**-4, 1.5*10**-5,3.5*10**-6,7.2*10**-7]
#plt.loglog(h_err, max_err) #PLOT OF MAXIMUM ERROR
#plt.xlabel('Step size h')
#plt.ylabel('Maximum relative error (log)')
#plt.title('Maximum relative error (log) for each step size')

plt.show()
x_e = np.linspace(x[1], x[n-1], n-1) #x axis for the relative error
#plt.plot(x_e, rel_error, label='u') #PLOT OF RELATIVE ERROR
#plt.xlabel('x')
plt.ylabel('log10 of relative error')
plt.title('log10 of relative error between numerical and exact solutions for n=100')



plt.plot(x, u, label='Numerical solution u(x)')
plt.plot(x, u_t, label = 'Exact solution u_t(x)')
plt.xlabel('x')
plt.ylabel('Solutions u(x), u_t(x)')
plt.title('Numerical u(x) and exact u_t(x) solutions for n=10 using LU decomposition')
plt.legend()
plt.show()


