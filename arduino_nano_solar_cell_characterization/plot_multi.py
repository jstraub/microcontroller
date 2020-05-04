#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt


pref=""
fs = ["./onSill/2.4v_small.csv","indoor/2.4v_small.csv", ]

pref = "./indoor/"
fs = ["6v_small.csv","6v_large.csv","2.4v_small.csv","3v_medium_amorph.csv","4v_medium_mono.csv"]

pref=""
fs = ["./indoor/6v_small.csv","indoor/6v_large.csv", "6v_small_morning.csv"]

plt.figure()
plt.subplot(1,2,1)
for f in fs:
    x = np.loadtxt(pref+f)
    i, u = x[:,0], x[:,1]
    plt.plot(u, i*1e3, lw=2, label=f)
plt.legend()
plt.xlabel("u [V]")
plt.ylabel("i [mA]")

plt.subplot(1,2,2)
for f in fs:
    x = np.loadtxt(pref+f)
    i, u = x[:,0], x[:,1]
    p = i*u
    plt.plot(u, p*1e3, lw=2, label=f)
plt.legend()
plt.xlabel("u [V]")
plt.ylabel("p [mW]")
plt.show()
