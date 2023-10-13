import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

with open('out.txt', 'r') as f:
    y = [float(line) for line in f]

x = []
for i in range(1, 37):
    x.append(i)

y_1 = y[0] + 0.0001 # На случай 0
y_a = [1]
for y_i in y:
    if y_i > 0:
        y_a.append(y_1/y_i)

plt.grid()
plt.plot(x, y_a, color='green', marker='o')
plt.xlabel('Количество процессов')
plt.ylabel('Ускорение')
plt.title('График ускорения')
plt.xlim((1, 32))
plt.show()

