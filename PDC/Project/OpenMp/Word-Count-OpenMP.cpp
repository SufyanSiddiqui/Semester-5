#include<iostream>
#include<fstream>
#include<omp.h>
#include<ctime>
#include<sstream>
#include<string>
using namespace std;
long long int Gcount=0;
void WordCounter(string fname, int tid)
{
	ifstream f1;
	fstream f2;
	long long int count=0;
	char c='\0';

	clock_t time_req;
	//ifstream in_file(fname.c_str(), ios::binary);
    //in_file.seekg(0, ios::end);
    //int file_size = in_file.tellg();
    //cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes"<<endl;
    //i/n_file.close();
	
	//int nt = file_size/100000;
	//cout<<nt<<endl;
	f1.open(fname.c_str(),ios::in);
	if(!f1)
	{
		cout<<"File not found"<<endl;
	}
	else
	{
		time_req = clock();
		
		
	while(!f1.eof())
		{
			f1>>c;
			if((c>=65 && c<=90) || (c>=97 && c<=122) )
			{
				count++;
				
			}	
		}
	
	time_req = clock() - time_req;	
	f1.close();
	#pragma omp barrier
	Gcount+=count;

	f2.open("Word-Count-Records.txt",ios::app);
	time_t now = time(0);
	tm *ltm = localtime(&now);

   // print various components of tm structure.
   //cout << "Year:" << 1900 + ltm->tm_year<<endl;
   //cout << "Month: "<< 1 + ltm->tm_mon<< endl;
   //cout << "Day: "<< ltm->tm_mday << endl;
   //cout << "Time: "<< 5+ltm->tm_hour << ":";
   //cout << 30+ltm->tm_min << ":";
   //cout << ltm->tm_sec << endl;
	cout<<"Word Count in "<<fname<<" is = "<<count<<endl;
	cout<<" Time taken: "<<(double)time_req/CLOCKS_PER_SEC << " seconds "<<endl;
	cout<<" Executed by Thread = "<<tid<<endl;
	f2<<"Word Count in " + fname + " is = ";
	f2<<count<<endl;
	f2 << "Year:" << 1900 + ltm->tm_year<<endl;
   f2 << "Month: "<< 1 + ltm->tm_mon<< endl;
   f2 << "Day: "<< ltm->tm_mday << endl;
   f2 << "Time: "<< 5+ltm->tm_hour << ":";
   f2 << 30+ltm->tm_min << ":";
   f2 << ltm->tm_sec << endl;
   f2<<"Time taken: "<<(double)time_req/CLOCKS_PER_SEC << " seconds "<<endl;
}
}

main()
{
	string fname;
	//fstream f1;
	int nt=2;
	int local_count=0;
	int tid=0;

	Insertion:	cout<<"Please enter number of threads (2-15)"<<endl;
	try{
		cin>>nt;
		if(nt<2 || nt>15){
			throw(nt);
		}
	}
	catch(int n){
		cout<<"Threads should be between 2 to 15"<<endl;
		cout<<"Execution Terminated"<<endl;
		goto Insertion;
	}
	clock_t time_req;
	omp_set_num_threads(nt);
	#pragma omp parallel num_threads(nt) //private(count,c) 
	#pragma omp for schedule(static)
	for(int i=1;i<=nt;i++)
	{
		//count=0;
		//c='\0';
		stringstream ss;
		ss<<i;
		string s;
		ss>>s;
		s+=".txt";
		WordCounter(s,omp_get_thread_num());
	}
	cout<<"Grand Count : "<<Gcount<<endl;
	//cout<<"Please enter the file name"<<endl;
	//cin>>fname;
	//fname=fname+".txt";
	//f1.open(fname.c_str(),ios::in);
	/*while(!f1.eof())
		{
			
			f1>>c;
			if((c>=65 && c<=90) || (c>=97 && c<=122) )
			{
				count++;
			}
			
			//tid=omp_get_thread_num();
			//cout<<"Thread "<<tid<<"is working"<<endl;	
			
	}
	
cout<<"count: "<<count;*/
//	WordCounter(fname);
	
}

