import itertools
import struct

import numpy as np
from matplotlib import pyplot as plt
from random import randint, random
import matplotlib.lines as mlines


plt.figure()

y2 = [0.00022, 0.00022, 0.000221, 0.000230, 0.000232, 0.000325]
y4 = [0.00072, 0.0008, 0.000968, 0.00113, 0.00123, 0.00258]
y6 = [0.0016, 0.00167, 0.0026, 0.00151, 0.0021, 0.00306]
y8 = [0.0019, 0.0019, 0.0031, 0.0033, 0.0026, 0.00775]
y10 = [0.0025, 0.0029, 0.0038, 0.0041, 0.0099, 0.0156]
y12 = [0.0053, 0.0045, 0.0047, 0.006, 0.012, 0.0226]
y14 = [0.0054, 0.006, 0.006, 0.0068, 0.0176, 0.0315]
y16 = [0.008, 0.00768, 0.00874, 0.0098, 0.0206, 0.036]

y = [y2, y4, y6, y8, y10, y12, y14, y16]
colors = ['r', 'g', 'b', 'c', 'm', 'y', 'lawngreen', 'crimson']

x = [2, 4, 8, 16, 32, 64]
procs = [2, 4, 6, 8, 10, 12, 14, 16]

for item, color in zip(y, colors):
    plt.plot(x, item, color)

squares = []

for i, c in zip(procs, colors):
    squares.append(mlines.Line2D([], [], color=c, marker='s',
                                 linestyle='None', markersize=10, label=f'{i} процессов(а)'))

plt.legend(handles=squares)
plt.title('График замеделения')
plt.xlabel('Размер словаря')
plt.ylabel('Время')
plt.xlim(2, 64)
plt.show()
