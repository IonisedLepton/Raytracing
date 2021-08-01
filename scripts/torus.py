from math import sin,cos
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d

# consts
N = 40
PI = 3.14159
R = 12
r = 4


theta = np.linspace(0,2*PI,N)
phi   = np.linspace(0,2*PI,N)

theta_cross_phi = [ [_theta,_phi] for _theta in theta for _phi in phi]

x = np.zeros((N,N))
y = np.zeros((N,N))
z = np.zeros((N,N))

for i,_theta in enumerate(theta):
	for j,_phi in enumerate(phi):
		x[i,j] = (R + r*cos(_phi))*cos(_theta)
		y[i,j] = (R + r*cos(_phi))*sin(_theta)
		z[i,j] = r*sin(_phi)


fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot_wireframe(x,y,z)

ax.set_xlim(-15,15)
ax.set_ylim(-15,15)
ax.set_zlim(-15,15)
plt.show()

