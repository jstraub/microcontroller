#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

f = "./indoorBrightNotDirectLight.csv"
f = "./indoorInLight.csv"
f = "./test.csv"

fig, ax1 = plt.subplots()
ax2 = ax1.twinx()
for f in ["./6v_small.csv","./6v_large.csv","./2.4v_small.csv","",""]:

    x = np.loadtxt(f)
    i, u = x[:,0], x[:,1]
    p = i*u
    
    for T in range(4, 30, 3):
        print("T={},\tR_series {}".format(T, -(u[0]-u[T]) / (i[0]-i[T])))
    for T in range(4, 30, 3):
        print("T={},\tR_shunt  {}".format(T, -(u[-1]-u[-T]) / (i[-1]-i[-T])))
    
    
    ax1.plot(u, i*1e3, "b-", lw=2, label="current")
    ax2.plot(u, p*1e3, "g-", lw=2, label="power")
    
ax1.set_xlabel("voltage [V]")
ax1.set_ylabel("current [mA]")
ax2.set_ylabel("power [mW]")
ax1.legend(loc="upper left")
ax2.legend(loc="upper right")
plt.show()
