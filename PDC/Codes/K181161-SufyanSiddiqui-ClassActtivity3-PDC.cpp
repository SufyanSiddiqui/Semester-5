#include<iostream>
#include <omp.h>
#include <stdlib.h>
using namespace std;

main()
{
	int a[2][2], b[2][2], mult[2][2];
	cout<<"Values for matrix a"<<endl;
	{
	for(int i=0;i<2;i++)
	{
		cout<<"row["<<i+1<<"]"<<endl;
		for(int j=0;j<2;j++)
		{
			
			cin>>a[i][j];
			mult[i][j]=0;
		}
	}
}
	cout<<"Values for matrix b"<<endl;
	for(int i=0;i<2;i++)
	{
		cout<<"row["<<i+1<<"]"<<endl;
		for(int j=0;j<2;j++)
		{
			
			cin>>b[i][j];
		}
	}
	
	#pragma omp parallel num_threads(4) 
	{
		#pragma omp for schedule(static)
		for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
        {

            for(int k = 0; k < 2; ++k)
            {
                mult[i][j] += a[i][k] * b[k][j];
            }
}
		
		
		
	}
	cout<<"Values for matrix mult"<<endl;
	{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			
			cout<<mult[i][j];
			cout<<"\t";
		}
		cout<<endl;
	}
}
}
