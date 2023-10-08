#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define N 2100
#define core_nums 8
double A[N][N], B[N][N], C[N][N];

typedef struct {
    int start_row;
    int end_row;
    int size;
} ThreadArgs;


void gemm(int start_row, int end_row,int size) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k <size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void *thread_multiply(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    gemm(thread_args->start_row, thread_args->end_row,thread_args->size);
    pthread_exit(NULL);
}

int main() {
    struct timeval start,finish;
    double duration; 
    int size[7] = {16 ,64, 256,128, 512,1024,2048};
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
    // 创建线程数组和参数数组
    pthread_t threads[core_nums];
    ThreadArgs thread_args[core_nums];

    for (int i=0;i<=6;i++)
        { 
            gettimeofday(&start,NULL);
            int chunk_size = size[i] / core_nums;
            for (int i = 0; i < core_nums; i++) {
                thread_args[i].start_row = i * chunk_size;
                thread_args[i].end_row = (i + 1) * chunk_size;
                thread_args[i].size = size[i];
                pthread_create(&threads[i], NULL, thread_multiply, (void *)&thread_args[i]);
            }

            // 等待所有线程完成
            for (int i = 0; i < core_nums; i++) {
                pthread_join(threads[i], NULL);
            }
            gettimeofday(&finish,NULL);
            double gflops = 2.0 * size[i] *size[i]*size[i];
            duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
            gflops = gflops/duration*1.0e-6/1000;
            fprintf(fp,"多线程矩阵乘法 core: 8,time = %lf,gflops:%lf\n",duration,gflops);
        }
    printf("计算结束！");
    return 0;
}
