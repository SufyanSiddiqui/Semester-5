

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 3
#define ROOT_PROCESS 0               
#define MASTER_TAG 1          
#define WORKER_TAG 2          

int main (int argc, char *argv[])
{
	int n_tasks,T_id, no_of_workers,destination,mtag,rows,index,i,j,k; 	
	int a[SIZE][SIZE] = {{1,2,3},{1,2,3},{1,2,3}};  
	int b[SIZE][SIZE] = {{4,5,6},{4,5,6},{4,5,6}};          
	int c[SIZE][SIZE];          
	i=0,j=0;
	for(i=0;i<SIZE;i++)
	for(j=0;j<SIZE;j++)
	c[SIZE][SIZE]=0; 
	MPI_Status status;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&T_id);

	MPI_Comm_size(MPI_COMM_WORLD,&n_tasks);

	if (n_tasks < 2 ) 
	{
	  printf("Number of Tasks must be greater than 2\n");
	  MPI_Abort(MPI_COMM_WORLD, 0);
	  exit(1);
	}

	no_of_workers = n_tasks-1;


	   if (T_id == ROOT_PROCESS)
	   {
	      index = 0;
	      mtag = MASTER_TAG;
	      for (destination=1; destination<=no_of_workers; destination++)
	      {
		 rows =1;  	
		 MPI_Send(&index, 3, MPI_INT, destination, mtag, MPI_COMM_WORLD);
		 MPI_Send(&rows, 3, MPI_INT, destination, mtag, MPI_COMM_WORLD);
		 MPI_Send(&a[index][0], rows*3, MPI_INT, destination, 			 mtag,MPI_COMM_WORLD);
		 MPI_Send(&b[index][0], rows*3, MPI_INT, destination, mtag, 			 MPI_COMM_WORLD);
		 index = index + rows;
	      }

	      mtag = WORKER_TAG;
	      for (i=1; i<=no_of_workers; i++)
	      {
		 MPI_Recv(&index, 3, MPI_INT, i, mtag, MPI_COMM_WORLD, &status);
		 MPI_Recv(&rows, 3, MPI_INT, i, mtag, MPI_COMM_WORLD, &status);
		 MPI_Recv(&c[index][0], rows*3, MPI_INT, i, mtag, 			 MPI_COMM_WORLD, &status);
		 
	      }

	   
	      printf("Resultant Matrix:\n");
	      for (i=0; i<SIZE; i++)
	      {
		 printf("\n"); 
		 for (j=0; j<SIZE; j++) 
		    printf("%d   ", c[i][j]);
	      }
		printf("\n");
	      
	      
	   }

	   if (T_id > ROOT_PROCESS)
	   {
	      mtag = MASTER_TAG;
	      MPI_Recv(&index, 3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, 		      &status);
	      MPI_Recv(&rows, 3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, 		      &status);
	      MPI_Recv(&a, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, 	&status);
	      MPI_Recv(&b, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD, 	&status);
	      printf("Child_Process %d is working at row_num %d\n",T_id,index+1);
	      for (i=0; i<rows; i++)
	    {
		 for (j=0; j<SIZE; j++)
		 {
			c[i][j] = a[i][j] + b[i][j];
			
		 }
	    }
		
	      mtag = WORKER_TAG;
	      MPI_Send(&index, 3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	      MPI_Send(&rows, 3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	      MPI_Send(&c, rows*3, MPI_INT, ROOT_PROCESS, mtag, MPI_COMM_WORLD);
	   }
	   MPI_Finalize();
}
