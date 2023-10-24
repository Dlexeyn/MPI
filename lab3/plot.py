from matplotlib import pyplot as plt
import matplotlib.lines as mlines

plt.figure()
y = [0.000131, 0.001712, 0.001256, 0.002097, 0.00664, 0.005245, 0.005245, 0.00897, 0.01702, 0.022]
y_a = []
y_1 = y[0]

for y_i in y:
    y_a.append(y_1/y_i)

x = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]


plt.plot(x, y_a, color='orange', marker='o')
plt.xlabel('Кол-во процессов в программе')
plt.ylabel('Ускорение')
plt.title('График ускорения')
plt.show()
