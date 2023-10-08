//cores为8一共分成8块
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#define N 2500
#define core_nums 8
double A[N][N], B[N][N], C[N][N];


// 矩阵乘法函数
void gemm(int start_row, int end_row,int size) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void block_gemm(int size)
{
    int chunk_size =  size/ core_nums,start_row,end_row;
        #pragma omp parallel for
    for (int i = 0; i < core_nums; i++) {
        start_row = i * chunk_size;
        end_row = (i + 1) * chunk_size;
        gemm(start_row,end_row,size);
    }
}



int main()
{
    struct timeval start,finish;
    double duration; 
    int size[7] = {16 ,64, 128,256, 512,1024,2048};
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
    
    for (int i=0;i<=6;i++)
        { 
            gettimeofday(&start,NULL);
            block_gemm(size[i]);
            gettimeofday(&finish,NULL);
            double gflops = 2.0 * size[i] *size[i]*size[i];
            duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
            gflops = gflops/duration*1.0e-6/1000;
            fprintf(fp,"size: %d ,openmp矩阵乘法time = %lf,gflops:%lf\n",size[i],duration,gflops);
        }
    printf("计算结束！");
    return 0;
}





