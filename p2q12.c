//compile--> mpicc p2q12.c -lm
//run--> mpirun -np 4 ./a.out
#include<stdio.h>
#include<mpi.h>
#include<math.h>
void main(int argc,char *argv[]){
    int rank,size,a,b,i;
    double c;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    a=0,b=1000,c=1.0;
    for(i=rank+a;i<=b;i+=size){
        if(sin((M_PI/180)*i)==c){
            printf("range(%d,%d), sin(%d)=%lf\n",a,b,i,sin((M_PI/180)*i));
        }
    }

    MPI_Finalize();
}