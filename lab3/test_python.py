#code:utf-8

import random
import numpy as np
from matplotlib import pyplot as plt
import matplotlib as mpl
import time
start = 128
end = 1152
inc = 128
critrion = 1e-5
results = []

font_name = "simhei"
mpl.rcParams['font.family']= font_name # 指定字体，实际上相当于修改 matplotlibrc 文件　只不过这样做是暂时的　下次失效
mpl.rcParams['axes.unicode_minus']=False # 正确显示负号，防止变成方框

def gemm(n):
    A = [[random.random()  for row in range(n)] for col in range(n)]
    B = [[random.random()  for row in range(n)] for col in range(n)]
    C = [[0 for row in range(n)] for col in range(n)]
    
    gflops = n*n*2*n
    elapsed_time = 1000000000
    C = [[0 for row in range(n)] for col in range(n)]  # np.dot没有累加，每次计算前清零
    start = time.time()
    #matrix multiplication
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]

    end = time.time()
    tmp_time = end - start
    if elapsed_time > tmp_time:
        elapsed_time = tmp_time

    np_elapsed_time = 1000000000
    start = time.time()
    C_np = np.dot(A, B)
    end  = time.time()
    tmp_time = end - start
    if np_elapsed_time > tmp_time:
        np_elapsed_time = tmp_time

    result = [n,n,n, gflops/elapsed_time*1.0e-6/1000, gflops/np_elapsed_time*1.0e-6/1000]
    print("%5d\t%5.2lf\t%5.2lf" % (n, gflops/elapsed_time*1.0e-6/1000, gflops/np_elapsed_time*1.0e-6/1000))
    return result

def plot_all(data):
    data = np.array(data)
    x = np.array([128, 256, 384, 512, 640, 768, 896, 1024])
    navie_gflops = data[:,-2]
    np_gflops = data[:,-1]
    with open("/home/lijun/hpc/lab3/time0.txt",'r') as file:
        lines = file.readlines()
    col1 = []
    col2 = []
    for line in lines:
        values = line.strip().split('\t')
        col1.append(float(values[0]))
        col2.append(float(values[1]))
        
    with open("/home/lijun/hpc/lab3/time1.txt",'r') as file:
        lines = file.readlines()
    col3 = []
    col4 = []
    for line in lines:
        values = line.strip().split('\t')
        col3.append(float(values[0]))
        col4.append(float(values[1]))
        
    with open("/home/lijun/hpc/lab3/time2.txt",'r') as file:
        lines = file.readlines()
    col5 = []
    col6 = []
    for line in lines:
        values = line.strip().split('\t')
        col5.append(float(values[0]))
        col6.append(float(values[1]))
        
    with open("/home/lijun/hpc/lab3/time3.txt",'r') as file:
        lines = file.readlines()
    col7 = []
    col8 = []
    for line in lines:
        values = line.strip().split('\t')
        col7.append(float(values[0]))
        col8.append(float(values[1]))

    plt.figure()
    plt.plot(x,col1,color = 'b',label = 'O-0')
    plt.plot(x,col3,color = 'r',label = 'O-1')
    plt.plot(x,col5,color = 'y',label = 'O-1')
    plt.plot(x,col7,color = 'g',label = 'O-3')
    plt.plot(x,navie_gflops,marker= 'd',label = "python naive")
    plt.xlabel("size")
    plt.ylabel("gflops")
    plt.xlim(0,1100)
    plt.xticks(x, x)
    plt.ylim(0,2.5)
    plt.legend()
    plt.grid(True)
    plt.title("不同优化方法下naive矩阵乘法")
    plt.savefig("naive.png")
    
    plt.figure()
    plt.plot(x,col2,color = 'b',label = 'O-0')
    plt.plot(x,col4,color = 'r',label = 'O-1')
    plt.plot(x,col6,color = 'y',label = 'O-1')
    plt.plot(x,col8,color = 'g',label = 'O-3')
    plt.plot(x,np_gflops,marker = 'd',label = "numpy")
    plt.xlabel("size")
    plt.ylabel("gflops")
    plt.xlim(0,1100)
    plt.xticks(x, x)
    plt.ylim(0,25)
    plt.title("不同优化方法下加速矩阵乘法")
    plt.grid(True)
    plt.legend()
    plt.savefig("speedup.png")
    
print("size\tnaive\tnumpy")
for n in range(start,end,inc):
    result1 = gemm(n)
    results.append(result1)
    print((np.array(results)[:,-1]))
plot_all(results)