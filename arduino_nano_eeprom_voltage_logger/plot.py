#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

x = np.loadtxt("./harvester0TransistorCycleSmoothed_3min.csv")
t = np.arange(x.shape[0])*169./3600.

plt.figure()
plt.plot(t, x[:,0], ".", label="adc0")
plt.plot(t, x[:,1], ".", label="adc1")
plt.xlabel("time [h]")
plt.ylabel("voltage [V]")
plt.legend()
plt.show()
