# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import matplotlib as mpl
font_name = "simhei"
mpl.rcParams['font.family']= font_name # 指定字体，实际上相当于修改 matplotlibrc 文件　只不过这样做是暂时的　下次失效
mpl.rcParams['axes.unicode_minus']=False # 正确显示负号，防止变成方框


x = [16 ,64, 256, 1024, 2048]
y1 = [0.195048,0.575508,0.693159,0.55585,0.435865]
y2 = [0.017174,6.472691,24.157258,44.086216,98.644173]

plt.plot(x,y1,label = 'naive朴素算法',color = 'blue')
plt.plot(x,y2,label = 'cblas加速算法',color = 'red')


plt.title('朴素算法与cblas加速矩阵乘法对比图')
plt.xlabel('矩阵大小')
plt.ylabel('gflops')
plt.legend()
plt.savefig('answer')
plt.show()