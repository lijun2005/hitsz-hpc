#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#include <cblas.h>
#define N 2050


int main()
{
    struct timeval start,finish;
    double duration; 
    int size[7] = {16 ,64, 128,256, 512,1024,2048};
    FILE  *fp;
    fp = fopen("time.txt","a");
    printf("开始计算！\n");
    srand(time(NULL));


    for (int i=0;i<=6;i++)
        { 
            double* A = (double*)malloc(sizeof(double) * size[i]*size[i]);
            double* B = (double*)malloc(sizeof(double) * size[i]*size[i]);
            double* C = (double*)malloc(sizeof(double) * size[i]*size[i]);

            for (int i =0;i<size[i]*size[i];i++)
            {
                A[i] = rand()%100+1.0;
                B[i] = rand()%100+1.0;
                C[i] = 0;
            }
            gettimeofday(&start,NULL);
            cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,size[i],size[i],size[i],1,A, size[i], B, size[i],0,C,size[i]);
            gettimeofday(&finish,NULL);
            double gflops = 2.0 * size[i] *size[i]*size[i];
            duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
            gflops = gflops/duration*1.0e-6/1000;
            fprintf(fp,"cblas加速矩阵乘法size = %d,gflops:%lf\n",size[i],gflops);
        }
    printf("计算结束！");
    return 0;
}