import numpy as np
import matplotlib.pylab as plt

data = np.genfromtxt("data.txt", delimiter = " , ")

time = data[:,0]

# Dado el orden de los cuerpos, hacer las gráficas
def graficarDat(data,cuerpos):
    plt.figure()
    for i in range(1,len(cuerpos)*2+1,2):
        plt.plot(data[:,i],data[:,i+1],label=cuerpos[i-int((i/2+1))])
    plt.legend()
    plt.savefig("Simulacion.png")
    plt.close()
    
graficarDat(data,['Sonda','Planeta1','Sol'])