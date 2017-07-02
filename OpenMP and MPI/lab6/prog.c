#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int a[] = { 50, 40, 30, 20, 10 };
  int sum = 0;
  int sum_plus = 0;
  int sum_minus = 0;
  int i = 0;
  int size = sizeof(a)/sizeof(int);
  int threads = atoi(argv[1]);
  printf("threads: %d\n", threads);
  
  /*#pragma omp parallel shared(a, sum) private(i) num_threads(5)
  {
    int num_threads = omp_get_num_threads();
    #pragma omp for
    for (i = 0; i < sizeof(a)/sizeof(int); i++) {
      int thread_num = omp_get_thread_num();
      if (i % 2 == 0) {
        sum += a[i];
        printf("+ in thread #%d/%d : sum = %d, i = %d, a[i] = %d\n", thread_num, num_threads, sum, i, a[i]);
      } else {
        sum -= a[i];
        printf("- in thread #%d/%d : sum = %d, i = %d, a[i] = %d\n", thread_num, num_threads, sum, i, a[i]);
      }
    }
  }*/

  /*#pragma omp parallel shared(a) reduction(+ : sum) private(i) num_threads(5)
  {
    int num_threads = omp_get_num_threads();
    #pragma omp for
    for (i = 0; i < size; i=i+2) {
      int thread_num = omp_get_thread_num(); 
      sum += a[i];
      printf("+ in thread #%d/%d : sum = %d, i = %d, a[i] = %d\n", thread_num, num_threads, sum, i, a[i]);
    }
  }
  printf("sum of a1+a3+a4+... = %d\n", sum);
  #pragma omp parallel shared(a) reduction(- : sum) private(i) num_threads(5)
  {
    int num_threads = omp_get_num_threads();
    #pragma omp for
    for (i = 1; i < size; i=i+2) {
      int thread_num = omp_get_thread_num(); 
      sum -= a[i];
      printf("- in thread #%d/%d : sum = %d, i = %d, a[i] = %d\n", thread_num, num_threads, sum, i, a[i]);
    }
  }
  printf("sum of -a2-a4-a5-... = %d\n", sum);
  printf("------------------------------\n");*/

  #pragma omp parallel shared(a) reduction(+ : sum_plus) reduction(- : sum_minus) private(i) num_threads(threads)
  {
    int num_threads = omp_get_num_threads();
    #pragma omp for
    for (i = 0; i < size; i=i+2) {
      int thread_num = omp_get_thread_num(); 
      sum_plus += a[i];
      sum_minus -= a[i+1];
      printf("thread #%d/%d : sum+ = %d, sum- = %d, i = %d, a[i] = %d, a[i+1] = %d\n", thread_num, num_threads, sum_plus, sum_minus, i, a[i], a[i+1]);
    }
  }
  printf("------------------------------\n");
  sum = sum_plus + sum_minus;
  printf("\na1-a2+a3-a4... = %d\n", sum);
  return 0;
}
