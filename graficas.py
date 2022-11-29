import numpy as np
import matplotlib.pylab as plt

data = np.genfromtxt("data.txt", delimiter = " , ")

time = data[:,0]
Ek = data[:,1]

# Dado el orden de los cuerpos, hacer las gráficas
def graficarDat(data,cuerpos):
    plt.figure()
    for i in range(2,len(cuerpos)*2-1,2):
        plt.plot(data[:,i],data[:,i+1],"--",label=cuerpos[i-int((i/2+1))])
    plt.plot(0,0,'.',label=cuerpos[-1])
    plt.xlabel("$x$")
    plt.ylabel("$y$")
    plt.legend()
    plt.savefig("Simulacion.png")
    plt.close()
    
graficarDat(data,['Sonda','Tierra','Sol', 'Jupiter'])

plt.figure()
plt.plot(time, Ek, label="Ek Vs t")
plt.legend()
plt.savefig("Energia.png")
plt.close()