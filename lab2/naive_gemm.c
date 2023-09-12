#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#define N 2050
double A[N][N], B[N][N], C[N][N];
void navie_gemm(double A[][N],double B[][N],int size)
{
    for(int i=0;i<size;i++)
        for(int j = 0;j<size;j++)
        {   
            C[i][j]=0 ;
            for(int p=0;p<size;p++)
                C[i][j] += A[i][p]*B[p][j];

        }

}


int main()
{
    struct timeval start,finish;
    double duration; 
    int size[5] = {16 ,64, 256, 1024, 2048};
    FILE  *fp;
    fp = fopen("time.txt","a");
    printf("开始计算！\n");
    srand(time(NULL));
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            A[i][j] = rand()%100+1.0;
            B[i][j] = rand()%100+1.0;
        }

    for (int i=0;i<=4;i++)
        { 
            gettimeofday(&start,NULL);
            navie_gemm(A,B,size[i]);
            gettimeofday(&finish,NULL);
            double gflops = 2.0 * size[i] *size[i]*size[i];
            duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
            gflops = gflops/duration*1.0e-6/1000;
            fprintf(fp,"朴素矩阵乘法size = %d,gflops:%lf\n",size[i],gflops);
        }
    printf("计算结束！");
    return 0;
}