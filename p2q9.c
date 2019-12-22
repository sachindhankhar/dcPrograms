//compile--> mpicc p2q9.c
//run--> mpirun -np 4 ./a.out
#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>
void main(int argc,char *argv[]){
    int rank,size,incount=0,outcount=0,totalincount=0,totaloutcount=0;
    double x,y,pi;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    srand(time(NULL));
    for(int i=0;i<10000;++i){
        x=-1.0+rand()/(RAND_MAX/(2.0));
        y=-1.0+rand()/(RAND_MAX/(2.0));
        if((x*x+y*y)<=1){
            incount++;
        }else outcount++;
    }

    MPI_Reduce(&incount,&totalincount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&outcount,&totaloutcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        pi=(4.0*totalincount/(totalincount+totaloutcount));
        printf("value of pi is: %lf\n",pi);
    }
    MPI_Finalize();
}