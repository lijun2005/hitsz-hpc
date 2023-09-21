#include <stdlib.h>
#include "sys/time.h"
#include "time.h"
#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]


void naive_gemm( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc );
void random_matrix( int m, int n, double *a, int lda );

double compare_matrices( int m, int n, double *a, int lda, double *b, int ldb );
double get_gflops(int size,struct timeval start,struct timeval end);

