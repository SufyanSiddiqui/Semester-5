#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define ROOT_PROCESS 0               
#define MASTER 1          
#define WORKER 2          

int main (int argc, char *argv[])
{
	int num_tasks,t_id, num_workers,dest,mtag,rows,index,i,j,k; 	
	int a[3][3] = {{1,3,5},{7,9,11},{13,15,17}};  
	int b[3][3] = {{2,4,6},{8,10,12},{14,16,18}};          
	int c[3][3];
	           
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&t_id);
	MPI_Comm_size(MPI_COMM_WORLD,&num_tasks);
	
	if (num_tasks < 2 ) 
	{
	  printf("Tasks must be greater than 2 \n");
	  MPI_Abort(MPI_COMM_WORLD, 0);
	  exit(1);
	}

	num_workers = num_tasks-1;


	   if (t_id == ROOT_PROCESS)
	   {
	      index = 0;
	      mtag = MASTER;
	      for (dest=1; dest<=num_workers; dest++)
	      {
	      	
		 rows =1;  	
		 MPI_Send(&index, 1, MPI_INT, dest, mtag, MPI_COMM_WORLD);
		 MPI_Send(&rows, 1, MPI_INT, dest, mtag, MPI_COMM_WORLD);
		 MPI_Send(&a[index][0], rows*3, MPI_INT, dest, mtag,MPI_COMM_WORLD);
		 MPI_Send(&b[index][0], rows*3, MPI_INT, dest, mtag, MPI_COMM_WORLD);
		 index = index + rows;
	      }

	      mtag = WORKER;
	      for (i=1; i<=num_workers; i++)
	      {
		 MPI_Recv(&index, 1, MPI_INT, i, mtag, MPI_COMM_WORLD, &status);
		 MPI_Recv(&rows, 1, MPI_INT, i, mtag, MPI_COMM_WORLD, &status);
		 MPI_Recv(&c[index][0], rows*3, MPI_INT, i, mtag, MPI_COMM_WORLD, &status);
		 
	      }

	   
	      printf("Resultant :\n");
	      for (i=0; i<3; i++)
	      {
		 printf("\n"); 
		 for (j=0; j<3; j++) 
		    printf("%2d   ", c[i][j]);
	      }
		printf("\n");
	      
	      
	   }

	   if (t_id > ROOT_PROCESS)
	   {
	      mtag = MASTER_TAG;
	      MPI_Recv(&index, 1, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, &status);
	      MPI_Recv(&rows, 1, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, &status);
	      MPI_Recv(&a, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, &status);
	      MPI_Recv(&b, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, &status);
	      printf("Child Process %d is at row_num %d\n",t_id,index+1);
	      for (i=0; i<rows; i++)
	    {
		 for (j=0; j<3; j++)
		 {
			c[i][j] = a[i][j] + b[i][j];
			
		 }
	    }
		
	      mtag = WORKER;
	      MPI_Send(&index, 1, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	      MPI_Send(&rows, 1, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	      MPI_Send(&c, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	   }
	   MPI_Finalize();
}
