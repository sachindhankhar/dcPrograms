//compile--> mpicc p2q11.c
//run--> mpirun -np 4 ./a.out
#include<stdio.h>
#include<mpi.h>
#include<string.h>
void main(int argc,char *argv[]){
    int rank,size,i,j,k,m1,n1,m2,n2,row,count=0;
    int a[100][100],b[100][100],c[100][100],data[]={0,0,0},taskSize=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0){
        printf("enter the size of first matrix row * col\n");
        scanf("%d %d",&m1,&n1);
        printf("enter first matrix\n");
        for(i=0;i<m1;i++){
            for(j=0;j<n1;++j){
                scanf("%d",&a[i][j]);
            }
        }
        printf("enter the size of second matrix row * col\n");
        scanf("%d %d",&m2,&n2);
        printf("enter second matrix\n");
        for(i=0;i<m2;i++){
            for(j=0;j<n2;++j){
                scanf("%d",&b[i][j]);
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&m1,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&n1,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&m2,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&n2,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&(a[0][0]),100*100,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&(b[0][0]),100*100,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if(rank==0){
        taskSize=m1*n2;                      //total no. of cells in result matrix
        for(i=0;i<taskSize;++i){             //receive till all cell values are obtained
            MPI_Recv(data,3,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            c[data[1]][data[2]]=data[0];
        }
    }else{
        for(row=rank-1;row<m1;row+=(size-1)){    //row assigned to process
            for(i=0;i<n2;++i){             //column of second matrix
                data[0]=0;                 //data[0] contains value of cell of result matrix
                for(j=0;j<n1;++j){         //iterate over first matrix row
                    data[0]+=a[row][j]*b[j][i];
                }
                data[1]=row;              //data[1] contains row no. of cell in result matrix
                data[2]=i;                //data[2] contains col no. of cell in result matrix
                MPI_Send(data,3,MPI_INT,0,0,MPI_COMM_WORLD);
            }
        }
    }

    if(rank==0){
        printf("result matrix is:\n");
        for(i=0;i<m1;++i){
            for(j=0;j<n2;++j){
                printf("%d ",c[i][j]);
            }printf("\n");
        }
    }

    MPI_Finalize();
}