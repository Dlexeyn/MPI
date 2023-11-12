from matplotlib import pyplot as plt
import matplotlib.lines as mlines

plt.figure()
y = [0.000206, 0.000760, 0.001453, 0.002455, 0.005216, 0.005808, 0.007145, 0.007444, 0.008633, 0.014419]
y_a = []
y_1 = y[0]

for y_i in y:
    y_a.append(y_1/y_i)

x = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]


plt.plot(x, y, color='orange', marker='o')
plt.xlabel('Кол-во процессов в программе')
plt.ylabel('Ускорение')
plt.title('График времени выполнения')
plt.show()
