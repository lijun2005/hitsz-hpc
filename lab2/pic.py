# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import matplotlib as mpl
font_name = "simhei"
mpl.rcParams['font.family']= font_name # 指定字体，实际上相当于修改 matplotlibrc 文件　只不过这样做是暂时的　下次失效
mpl.rcParams['axes.unicode_minus']=False # 正确显示负号，防止变成方框


x = [16 ,64, 256, 1024, 2048]
y1 = [0.000026,0.000828,0.048285,3.251161,38.788221]
y2 = [0.000048,0.000228,0.013531,0.031032,0.131876]

plt.plot(x,y1,label = 'naive朴素算法',color = 'blue')
plt.plot(x,y2,label = 'cblas加速算法',color = 'red')


plt.title('朴素算法与cblas加速矩阵乘法对比图')
plt.xlabel('矩阵大小')
plt.ylabel('时间/s')
plt.legend()
plt.savefig('answer')
plt.show()