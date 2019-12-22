//compile--> mpicc p2q8.c
//run--> mpirun -np 4 ./a.out
#include<stdio.h>
#include<mpi.h>
#include<string.h>
void main(int argc,char *argv[]){
    int rank,size;
    int vec1[12],vec2[12],i,res=0,partial=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    for(i=0;i<12;++i){
        vec1[i]=i;
        vec2[i]=2*i;
    }

    for(i=rank*(size-1);i<rank*(size-1)+(12/size);++i){
        partial+=vec1[i]*vec2[i];
    }
    printf("partial sum by process  %d of %d is %d\n",rank,size,partial);
    MPI_Reduce(&partial,&res,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("dot product of vectors :\n");
        for(int i=0;i<12;++i){
            printf("%d ,",vec1[i]);
        }printf("\n");
        for(int i=0;i<12;++i){
            printf("%d ,",vec2[i]);
        }printf("\n");
        printf("is: %d\n",res);
    }
    MPI_Finalize();
}