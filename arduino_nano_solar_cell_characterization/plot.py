#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

f = "./indoorBrightNotDirectLight.csv"
f = "./indoorInLight.csv"

x = np.loadtxt(f)
i, u = x[:,0], x[:,1]
p = i*u

for T in range(4, 30, 3):
    print("T={}, R_0 {}".format(T, -(u[0]-u[T]) / (i[0]-i[T])))
for T in range(4, 30, 3):
    print("T={}, R_e {}".format(T, -(u[-1]-u[-T]) / (i[-1]-i[-T])))


fig, ax1 = plt.subplots()

ax2 = ax1.twinx()
ax1.plot(u, i*1e3, 'g-')
ax2.plot(u, p*1e3, 'b-')

ax1.set_xlabel("voltage [V]")
ax1.set_ylabel("current [mA]")
ax2.set_ylabel("power [mW]")
plt.show()
