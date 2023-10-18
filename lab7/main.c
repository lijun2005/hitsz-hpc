#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void gemm(int line,int size,double *result,double *buffer,double *b){
    for (int m=0;m<line;m++){
        for (int j=0;j<size;j++){
            double middle =0;
            for (int k=0;k<size;k++)
                middle  += buffer[m*size+k] * b[k*size+j];
            result[m*size+j] = middle;
        }
    }
}

int main(int argc, char ** argv)
{
    double start ,end ,*a,*b,*c,*result,*buffer;
    int i,j,k,l,rank,numprocs,line;
    int scale[7] = {16 ,64, 128,256, 512,1024,2048};
        MPI_Init(0,0);
    for (int count =0;count<7;count++){
        int size = scale[count];
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
        line = size/numprocs;
        a = (double*) malloc(sizeof(double)*size *size);
        b = (double*) malloc(sizeof(double)*size*size);
        c = (double*) malloc(sizeof(double)*size *size);
        result = (double*) malloc(sizeof(double)*size *line);
        buffer = (double*) malloc(sizeof(double)*size *line);
        srand(time(NULL));
        if (rank==0){
            FILE  *fp;
          fp = fopen("time.txt","a");
            //initialize
            for (int i=0;i<size;i++)
                for(int j=0;j<size;j++){
                    a[i*size +j] =rand()%100+1.0;
                    b[i*size +j] =rand()%100+1.0;
                    c[i*size +j] =0;
                }

            // Initialize a, b, c here

            start = MPI_Wtime();
            //send
            for(int i=1;i<numprocs;i++){
                MPI_Send(b,size*size,MPI_DOUBLE,i,0,MPI_COMM_WORLD);
                MPI_Send(a + (i-1)*size*line,size*line,MPI_DOUBLE,i,1,MPI_COMM_WORLD);
            }
            //receive and combine
            for (int i=1;i<numprocs;i++){
                MPI_Recv(result,line*size,MPI_DOUBLE,i,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    for (int m=0;m<line;m++){
                        for (int j=0;j<size;j++){
                            c[((i-1)*line+m)*size+j] = result[m*size+j];
                        }
                    }
            }
            for (int i = (numprocs-1)*line;i<size;i++)
                for(int j=0;j<size;j++)
                    for (int k=0;k<size;k++)
                        c[i*size+j] = a[i*size+k] * b[k*size+j];
            end = MPI_Wtime();
            double gflops = 2.0 * size *size*size;
            double duration  = end - start;
            gflops = gflops/duration*1.0e-6/1000;
            fprintf(fp,"mpi矩阵乘法 size= %d,time = %lf,gflops:%lf,progress:%d \n",size,duration,gflops,numprocs);
            fclose(fp);

            }
        else 
        {
            MPI_Recv(b,size*size,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(buffer,line*size,MPI_DOUBLE,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            gemm(line,size,result,buffer,b);
            MPI_Send(result,line*size,MPI_DOUBLE,0,3,MPI_COMM_WORLD);
        }
    }
            MPI_Finalize();
    return 0;

} 
