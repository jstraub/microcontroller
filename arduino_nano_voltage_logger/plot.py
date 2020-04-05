#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

x = np.loadtxt("./liIonDischarge.csv")
xSmooth = np.convolve(x[:,1], np.ones(60)/60., mode="valid")

plt.figure()
plt.plot(x[:,1], label="raw")
plt.plot(xSmooth, label="smooth")
plt.legend()
plt.show()
