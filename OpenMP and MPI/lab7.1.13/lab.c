#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <math.h>

#define N 11

double a[N];
double f = 3.14;

int main(void){

  a[0]=f;
  int i;
  #pragma omp parallel for
  for (i = 1; i < N; i++)
  {
    a[i] = pow(f, i+2);
  }

  return 0;
}
