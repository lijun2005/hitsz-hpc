# -*- coding: UTF-8 -*-
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties



x = [16 ,64, 256, 1024, 2048]
y1 = [0.000026,0.000828,0.048285,3.251161,38.788221]
y2 = [0.000048,0.000228,0.013531,0.031032,0.131876]

plt.plot(x,y1,label = 'naive',color = 'blue')
plt.plot(x,y2,label = 'cblas',color = 'red')


plt.title('naive and  cblas')
plt.xlabel('arrat shape')
plt.ylabel('time/s')

plt.savefig('answer')
plt.show()