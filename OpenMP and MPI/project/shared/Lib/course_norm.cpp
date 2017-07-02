#include <cstdlib>
#include <stdio.h>
#include <string>
#include <math.h>
#include <omp.h>
#include "course.h"

using namespace std;

bool is_sorted(int *a, int n)
{
  while ( --n >= 1 ) {
    if ( a[n] < a[n-1] ) return false;
  }
  return true;
}
 
void shuffle(int *a, int n)
{
 // printf("Shuffle\n");
	int i, t, r;
  for(i=0; i < n; i++) {
    t = a[i];
    r = rand() % n;
    a[i] = a[r];
    a[r] = t;
  }
}
 
void bogosort(int *a, int n)
{
	//#pragma parralel
  while ( !is_sorted(a, n) ) {
	  shuffle(a, n);
	  for(int i = 0; i < n; i++) {
		 printf("%d ", a[i]);
	  }
	  printf("\n");
  }
	  
  for(int i = 0; i < n; i++) {
	  printf("%d ", a[i]);
  }
}


int start(int *a, int n ) {
    unsigned int start_time =  clock(); 
	omp_set_num_threads(3);	
	bogosort(a, n);
	
	unsigned int end = clock();
	return end - start_time;
	
	
}


int main() {
  
}
