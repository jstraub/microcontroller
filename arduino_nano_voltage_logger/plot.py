#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

x = np.loadtxt("./liIonDischarge.csv")
t = np.arange(x.shape[0])*1000./1024.
xSmooth = np.convolve(x[:,1], np.ones(60)/60., mode="valid")

plt.figure()
plt.plot(x[:,1], "b", alpha=0.5, label="raw")
plt.plot(xSmooth, "r", label="smooth")
plt.xlabel("time [s]")
plt.ylabel("voltage [V]")
plt.legend()
plt.show()
