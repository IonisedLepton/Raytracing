from math import sin,cos
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d
import os

dir_path = os.path.dirname(os.path.realpath(__file__))

# consts
N = 40
M = 40
PI = 3.14159
R = 3
r = 1


theta = np.linspace(0,2*PI,N)
phi   = np.linspace(0,2*PI,M)

theta_cross_phi = [ [_theta,_phi] for _theta in theta for _phi in phi]

x = np.zeros((N,M))
y = np.zeros((N,M))
z = np.zeros((N,M))

for i,_theta in enumerate(theta):
	for j,_phi in enumerate(phi):
		x[i,j] = (R + r*cos(_phi))*cos(_theta)
		y[i,j] = (R + r*cos(_phi))*sin(_theta)
		z[i,j] = r*sin(_phi)

# plot the torus
# fig = plt.figure()
# ax = plt.axes(projection='3d')
# ax.plot_wireframe(x,y,z)
# 
# ax.set_xlim(-15,15)
# ax.set_ylim(-15,15)
# ax.set_zlim(-15,15)
# plt.show()


# generate triangles
triangles_fwd_indexing = np.zeros((N-1,M-1,3,3))
triangles_bwd_indexing = np.zeros((N-1,M-1,3,3))

for i in range(N-1):
	for j in range(M-1):
		triangles_fwd_indexing[i,j] = np.array([
								[x[i,j],   y[i,j],   z[i,j]],
								[x[i+1,j], y[i+1,j], z[i+1,j]],
								[x[i,j+1], y[i,j+1], z[i,j+1]],
								])

		triangles_bwd_indexing[i,j] = np.array([
								[x[i+1,j+1], y[i+1,j+1], z[i+1,j+1]],
								[x[i,j+1],   y[i,j+1],   z[i,j+1]],
								[x[i+1,j],   y[i+1,j],   z[i+1,j]],
								])

# write out triangles
f = open(os.path.join(dir_path,r"../assets/torus.raw"),"w")

for i in range(N-1):
	for j in range(M-1):
		triangle_fwd = np.ravel(triangles_fwd_indexing[i,j])
		triangle_bwd = np.ravel(triangles_bwd_indexing[i,j])

		triangle_raw_fwd = " ".join(map(str,triangle_fwd))
		triangle_raw_bwd = " ".join(map(str,triangle_bwd))

		f.write(triangle_raw_fwd + "\n")
		f.write(triangle_raw_bwd + "\n")

f.close()






















