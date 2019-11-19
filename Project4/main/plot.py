import matplotlib.pyplot as plt
import numpy as np


x = []
y = []

file = open("Random.txt", "r")
MC = float(file.readline())
T = file.readline()
T = T.split(" ")
T_s = float(T[0])
T_e = float(T[1])
for i in file:
    data = i.split()
    x.append(float(data[0]))
    y.append(float(data[2]))


a = []
b = []

file = open("Ones.txt", "r")
MC = float(file.readline())
T = file.readline()
T = T.split(" ")
T_s = float(T[0])
T_e = float(T[1])
for i in file:
    data = i.split()
    a.append(float(data[0]))
    b.append(float(data[2]))

lin = np.linspace(0, MC/100, MC/10000)




plt.plot(lin, a, label="Ones")
plt.plot(lin, x, label="Random")
plt.xlabel("Monte Carlo Cycles")
plt.ylabel("Energy")
plt.legend()
plt.show()
plt.plot(lin, b, label="Ones")
plt.plot(lin, y, label="Random")
plt.xlabel("Monte Carlo Cycles")
plt.ylabel("Magnetization")
plt.legend()
plt.show()

#Python3 plot.py
