//compile--> mpicc p2q7.c
//run--> mpirun -np 4 ./a.out
//to install open mpi in ubuntu--> sudo apt install libopenmpi-dev
#include<stdio.h>
#include<mpi.h>
#include<string.h>
int main(int argc,char *argv[]){

    int rank,size,sender;
    char message[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status stat;

    sprintf(message,"hello from %d of %d\n",rank,size);

    if(rank==0){
        for(sender=1;sender<size;++sender){
            MPI_Recv(&message,sizeof(message),MPI_BYTE,sender,1,MPI_COMM_WORLD,&stat);
            fputs(message,stdout);
        }
    }else{
        MPI_Send(&message,sizeof(message),MPI_BYTE,0,1,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}