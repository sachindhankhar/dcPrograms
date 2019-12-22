//set no. of processors to more than 4 to distribute them ,say 16
//compile--> mpicc p2q10.c
//run--> mpirun -np 16 ./a.out
#include<stdio.h>
#include<mpi.h>
void main(int argc,char *argv[]){
    int rank,size,color,newRank,newSize,commLen;
    MPI_Comm newCommunicator;
    char commName[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    color=rank/4;

    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&newCommunicator);

    MPI_Comm_rank(newCommunicator,&newRank);
    MPI_Comm_size(newCommunicator,&newSize);


    printf("process %d of %d in MPI_COMM_WORLD , %d of %d in Communicator: %d\n",rank,size,newRank,newSize,color+1);

    MPI_Comm_free(&newCommunicator);
    MPI_Finalize();
}
