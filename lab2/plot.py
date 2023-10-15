from matplotlib import pyplot as plt
import matplotlib.lines as mlines

plt.figure()

y2 = [0.000109, 0.000112, 0.000114, 0.000128, 0.000130, 0.000141]
y4 = [0.000343, 0.000353, 0.000355, 0.000367, 0.000378, 0.000393]
y6 = [0.00065, 0.000701, 0.000832, 0.000903, 0.00096, 0.001]
y8 = [0.0018, 0.0020, 0.0022, 0.0023, 0.0023, 0.0024]
y10 = [0.0034, 0.0037, 0.0038, 0.0041, 0.0042, 0.0045]
y12 = [0.0065, 0.0067, 0.00675, 0.0068, 0.0072, 0.0084]
y14 = [0.007, 0.0084, 0.0094, 0.013, 0.015, 0.0167]
y16 = [0.015, 0.0175, 0.0256, 0.028, 0.0306, 0.041]

y = [y2, y4, y6, y8, y10, y12, y14, y16]
y_a = []

for y_i in y:
    y_a_i = []
    y_1 = y_i[0]
    for i in y_i:
        y_a_i.append(y_1 / i)
    y_a.append(y_a_i)

colors = ['r', 'g', 'b', 'c', 'm', 'y', 'lawngreen', 'crimson']

x = [1, 2, 3, 4, 5, 6]
procs = [2, 4, 6, 8, 10, 12, 14, 16]

for item, color in zip(y_a, colors):
    plt.plot(x, item, color)

squares = []

for i, c in zip(procs, colors):
    squares.append(mlines.Line2D([], [], color=c, marker='s',
                                 linestyle='None', markersize=10, label=f'{i} процессов(а)'))

plt.legend(handles=squares)
plt.xlabel('Множитель размера массива')
plt.ylabel('Время')
plt.title('График замедления')
plt.show()
