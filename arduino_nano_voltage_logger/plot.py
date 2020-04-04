#!/usr/bin/env python

import numpy as np 
import matplotlib.pyplot as plt

x = np.loadtxt("./liIonDischarge.csv")

plt.figure()
plt.plot(x[:,1])
plt.show()
