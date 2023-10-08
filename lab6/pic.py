# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import matplotlib as mpl
font_name = "simhei"
mpl.rcParams['font.family']= font_name # 指定字体，实际上相当于修改 matplotlibrc 文件　只不过这样做是暂时的　下次失效
mpl.rcParams['axes.unicode_minus']=False # 正确显示负号，防止变成方框


x = [16 ,64, 128,256,512,1024, 2048]
gflops_naive = [0.227556, 0.585143, 0.695804, 0.702328, 0.709177, 0.624277, 0.530429]
gflops_multithreaded = [0.000175, 0.002811, 0.011453, 0.065688, 0.257837, 0.841154, 4.122564]
gflops_cblas = [0.132129, 2.122623, 0.537249, 23.848210, 39.709387, 51.305245, 90.169787]
gflops_openmp = [0.020583, 3.318278, 3.898052, 3.447137, 3.670661, 3.815626, 2.71690]

plt.plot(x, gflops_naive, label='naive朴素算法', color='blue', linestyle='-')
plt.plot(x, gflops_multithreaded, label='多线程算法', color='red', linestyle='--')
# plt.plot(x, gflops_cblas, label='cblas加速算法', color='green', linestyle='-.')
plt.plot(x, gflops_openmp, label='openmp算法', color='purple', linestyle=':')

plt.title('各种算法对比图')
plt.xlabel('矩阵大小')
plt.ylabel('gflops')
plt.legend()
plt.savefig('result1.png')
plt.show()
