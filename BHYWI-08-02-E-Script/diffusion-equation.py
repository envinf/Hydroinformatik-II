import math
import matplotlib.pylab as plt
PI = 3.14159265358979323846
numPoints = 10
alpha = 1.0
t = [0.1,0.5,1.0,2.0]
x = []
y = []
for n in t:
    for i in range(0,numPoints+1):
        x.append(float(i)/float(numPoints))
        y.append(math.sin(PI*x[i]) * math.exp(-alpha*n*n))
    plt.plot(x,y,color='red',marker="o")
    x = []
    y = []
plt.xlabel('x')
plt.ylabel('u')
plt.axis('tight')
plt.savefig("diffusion-equation.png")
plt.show()
