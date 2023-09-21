#include <stdlib.h>
#include "sys/time.h"
#include "time.h"
#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]
#define abs( x ) ( (x) < 0.0 ? -(x) : (x) )


void naive_gemm( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc )
{
  int i, j, p;


  for ( i=0; i<m; i++ ){        
    for ( j=0; j<n; j++ ){        
     C( i,j ) = 0;
      for ( p=0; p<k; p++ ){       
	C( i,j ) =  C( i,j ) +  A( i,p ) * B( p,j );
      }
    }
  }
}

void random_matrix( int m, int n, double *a, int lda )
{
  double drand48();
  int i,j;

  for ( j=0; j<n; j++ )
    for ( i=0; i<m; i++ )
      A( i,j ) = 2.0 * drand48( ) - 1.0;
}



double compare_matrices( int m, int n, double *a, int lda, double *b, int ldb )
{
  int i, j;
  double max_diff = 0.0, diff;

  for ( j=0; j<n; j++ )
    for ( i=0; i<m; i++ ){
      diff = abs( A( i,j ) - B( i,j ) );
      max_diff = ( diff > max_diff ? diff : max_diff );
    }

  return max_diff;
}

double get_gflops(int size,struct timeval start,struct timeval finish)
{
    double gflops = 2.0 * size *size*size;
    double duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
    gflops = gflops/duration*1.0e-6/1000;
    return gflops;
}