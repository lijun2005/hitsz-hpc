#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#include <cblas.h>
#include "function.h"

int size[8] = {128, 256, 384, 512, 640, 768, 896, 1024};


int main()
{
    double *a,*b,*c;
    struct timeval start,finish;
    FILE  *fp;
    fp = fopen("time0.txt","a");
    for (int i=0;i<=7;i++)
    {
        int m = size[i];
        a = ( double * ) malloc(  m*m * sizeof( double ) );  
        b = ( double * ) malloc( m*m * sizeof( double ) );
        c = ( double * ) malloc( m*m * sizeof( double ) );
        random_matrix(m,m, a,m);
        random_matrix(m,m, b,m);
        random_matrix(m,m, c,m);


        gettimeofday(&start,NULL);
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans,m,m,m,1,a, m, b, m,0,c,m);
        gettimeofday(&finish,NULL);
        double gflops1 = get_gflops(m,start,finish);


        gettimeofday(&start,NULL);
        naive_gemm(m,m,m,a,m,b,m,c,m);
        gettimeofday(&finish,NULL);
        double gflops2 = get_gflops(m,start,finish);
        fprintf(fp,"%.3lf\t%.3lf\n",gflops2,gflops1);
        printf(" %d\t%.3lf\t%.3lf\n",m,gflops2,gflops1);
    }
}
