import numpy as np
import matplotlib.pyplot as plt

# 创建网格
x = np.linspace(-3, 3, 400)
y = np.linspace(-3, 3, 400)
X, Y = np.meshgrid(x, y)

# 定义约束条件
g1 = X**2 + Y**2 - 4
g2 = 1 - X*Y
g3 = 1 - X - Y

# 创建图形
plt.figure(figsize=(10, 10))

# 绘制约束条件
plt.contour(X, Y, g1, [0], colors='r', linewidths=2, label='x^2 + y^2 = 4')
plt.contour(X, Y, g2, [0], colors='g', linewidths=2, label='xy = 1')
plt.contour(X, Y, g3, [0], colors='b', linewidths=2, label='x + y = 1')

# 绘制同心圆
circle1 = plt.Circle((2, 1), 0.5, color='purple', fill=False, linestyle='--', label='Circle r=0.5')
circle2 = plt.Circle((2, 1), 1, color='orange', fill=False, linestyle='--', label='Circle r=1')
circle3 = plt.Circle((2, 1), 1.5, color='cyan', fill=False, linestyle='--', label='Circle r=1.5')
plt.gca().add_artist(circle1)
plt.gca().add_artist(circle2)
plt.gca().add_artist(circle3)

# 标记(2,1)点
plt.plot(2, 1, 'ko', markersize=8, label='(2,1)')

# 标记最优解点 [1.78885, 0.894427]
optimal_x, optimal_y = 1.78885, 0.894427
plt.plot(optimal_x, optimal_y, 'r*', markersize=10, label='Optimal (1.78885, 0.894427)')

# 设置图形属性
plt.xlim(-3, 3)
plt.ylim(-3, 3)
plt.axhline(y=0, color='k', linestyle='-', linewidth=0.5)
plt.axvline(x=0, color='k', linestyle='-', linewidth=0.5)
plt.title('Constraint Curves, Concentric Circles, and Optimal Solution')
plt.xlabel('x')
plt.ylabel('y')
plt.legend(loc='upper left', bbox_to_anchor=(1, 1))
plt.grid(True)

# 显示图形
plt.tight_layout()
plt.show()