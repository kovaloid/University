#include <omp.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

void func()
{
	for(int i= 0; i < 500000; i++)
		rand();
}

int main()
{ 
	omp_set_num_threads(4);
	cout << "max threads: " << omp_get_max_threads() << endl;

	#pragma omp parallel for
		for (int i= 0; i < 100; i++)
			{ cout << 0; func(); }
	#pragma omp parallel
	{
		#pragma omp single
			cout << "\nnumber of threads: " << omp_get_num_threads() << endl;
		#pragma omp sections nowait
		{
			#pragma omp section
				for (int i= 0; i < 10; i++)
					{ cout << 1; func(); }
			#pragma omp section
				for (int i= 0; i < 20; i++)
					{ cout << 2; func(); }
				
		}
		#pragma omp barrier
			for (int i= 0; i < 10; i++)
				{ cout << 3; func(); }
	}

//------------------------------------------------------------------

	cout << "\n\n\nstart testing..." <<endl;
	int MaxProc = omp_get_num_procs();
	cout << "number of processors: " << MaxProc << endl;

	cout << "set number of threads: " << 2 << endl;
	omp_set_num_threads(2);

	int StartTime = GetTickCount();

	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 0; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 1; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 2; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 3; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
		}
	}

	int EndTime = GetTickCount();
	cout << "time of work: " << EndTime - StartTime << endl;

	cout << "set number of threads: " << 3 << endl;
	omp_set_num_threads(3);

	StartTime = GetTickCount();

	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 0; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 1; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 2; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 3; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
		}
	}

	EndTime = GetTickCount();
	cout << "time of work: " << EndTime - StartTime << endl;

	cout << "set number of threads: " << 4 << endl;
	omp_set_num_threads(4);

	StartTime = GetTickCount();

	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 0; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 1; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 2; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
			#pragma omp section
				for (int i= 0; i < 5; i++)
					{ cout << "  section: " << 3; cout << "  thread: " << omp_get_thread_num() << endl; func(); }
		}
	}

	EndTime = GetTickCount();
	cout << "time of work: " << EndTime - StartTime << endl;

//------------------------------------------------------------------

	omp_lock_t my_lock;
	omp_init_lock(&my_lock);

	int arr[100];
	cout<< endl << endl << "Write array:" << endl;

    #pragma omp parallel num_threads(2)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				  int tid = omp_get_thread_num();
				  int i, j = 0;

				  for (i = 0; i < 5; ++i) {
					 omp_set_lock(&my_lock);
					 printf_s("Thread %d - starting locked region\n", tid);
					 arr[j] = j;
					 cout << "  put data: " << arr[j] << " to index: " << j << endl;
					 j = j + 2;
					 printf_s("Thread %d - ending locked region\n", tid);
					 omp_unset_lock(&my_lock);
					 func();
				  }
			}
			#pragma omp section
			{
				  int tid = omp_get_thread_num();
				  int i, j = 1;

				  for (i = 0; i < 5; ++i) {
					 omp_set_lock(&my_lock);
					 printf_s("Thread %d - starting locked region\n", tid);
					 arr[j] = j;
					 cout << "  put data: " << arr[j] << " to index: " << j << endl;
					 j = j + 2;
					 printf_s("Thread %d - ending locked region\n", tid);
					 omp_unset_lock(&my_lock);
					 func();
				  }
			}
		}
	}

	cout<< endl << endl << "Read array:" << endl;

	#pragma omp parallel num_threads(2)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				  int tid = omp_get_thread_num();
				  int i, j = 0;

				  for (i = 0; i < 5; ++i) {
					 omp_set_lock(&my_lock);
					 printf_s("Thread %d - starting locked region\n", tid);
					 cout << "  array[" << j << "] = " << arr[j] << endl;
					 j = j + 2;
					 printf_s("Thread %d - ending locked region\n", tid);
					 omp_unset_lock(&my_lock);
					 func();
				  }
			}
			#pragma omp section
			{
				  int tid = omp_get_thread_num();
				  int i, j = 1;

				  for (i = 0; i < 5; ++i) {
					 omp_set_lock(&my_lock);
					 printf_s("Thread %d - starting locked region\n", tid);
					 arr[j] = j;
					 cout << "  array[" << j << "] = " << arr[j] << endl;
					 j = j + 2;
					 printf_s("Thread %d - ending locked region\n", tid);
					 omp_unset_lock(&my_lock);
					 func();
				  }
			}
		}
	}

    omp_destroy_lock(&my_lock);

	getch();
}