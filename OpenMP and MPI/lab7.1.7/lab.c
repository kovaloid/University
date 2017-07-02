#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <math.h>

#define N 11

double a[N];
double y,x;

int main(void){

  int i;
  #pragma omp parallel for private(x, y, i)
  for (i = 0; i < N; i++)
  {
    int common = i/N*3.14;
    y = i*sin(common);
    x = i*cos(common);
    a[i] = y+x;
  }

  return 0;
}
