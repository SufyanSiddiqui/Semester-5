#include <iostream>
#include <omp.h>
using namespace std;
double CalcMeanSolo(int A[10])
{
	int sum=0;
	#pragma omp parallel
	{
	#pragma omp for
	for(int i=0;i<10;i++)
	{
		sum+=A[i];
	}
}

	return (sum/10);
	
}
double CalcMeanAll(int A[],int B[],int C[])
{
	int sum=0;
	#pragma omp parallel
	{
	#pragma omp for
	for(int i=0;i<10;i++)
	{
		sum+=A[i]+B[i]+C[i];
	}
}
	return(sum/30);
}
main()
{
	int A1[10]= {1,4,9,12,6,14,3,7,11,5};
	int A2[10]={44,5,6,17,9,13,15,1,3,22};
	int A3[10]={33,22,18,17,19,4,5,34,27,20};
	double a=0,b=0,c=0;
	
	
	#pragma omp parallel num_threads(3)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				a=CalcMeanSolo(A1);	
			}
			#pragma omp section
			{
				b=CalcMeanSolo(A2);
			}
			#pragma omp section
			{
				c=CalcMeanSolo(A3);
			}
		}
		
	}
	#pragma omp barrier
	cout<<"Mean of A1: "<<a<<endl;
	cout<<"Mean of A2: "<<b<<endl;
	cout<<"Mean of A3: "<<c<<endl;
	cout<<"Mean of All Arrays: "<<CalcMeanAll(A1,A2,A3)<<endl;
	
}
