#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 4

void fillMatrix(int a[][SIZE], int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < SIZE; j++) {
      a[i][j] = rand() % 5 + 1;
    }
  }
}

void printMatrix(int a[][SIZE], int N) {
  printf("Matrix [%d][%d]:\n", N, SIZE);  
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < SIZE; j++){
      printf(" \t%d", a[i][j]);
    }
    printf("\n\n");
  }     
}

int main(int argc, char** argv)
{
  int N = 3;
  if (argc > 1) {
    N = atoi(argv[1]);
  }
  int a[N][SIZE];
  int threads = 5;
  if (SIZE > 5) {
    threads = SIZE;
  }

  printf("Number of threads: %d\n", threads);

  fillMatrix(a, N);
  printMatrix(a, N);

  int row_max = pow(SIZE, N);
  int col_max = N;
  int results[row_max][col_max];
 
  int k, i, j, n, m;
  #pragma omp parallel for shared(results, a, row_max, col_max) private(i, j, n, m, k) num_threads(threads)
  for (i = 0; i < col_max; i++) {
    k = pow(SIZE, i);
    for (j = 0; j < SIZE; j++) {
      for (n = 0; n < row_max; n += pow(SIZE, i+1)) {
        for (m = 0; m < k; m++) {
          results[n+m+k*j][i] = a[i][j];
          //printf("[%d][%d]\t<->\t[%d][%d]\n", n+m+k*j, i, i, j);
        }
      }
    }
  }

  printf("\n\nRESULT: \n");
  for(int i = 0; i < row_max; i++) {
    printf(" { %d", results[i][0]);
    for(int j = 1; j < col_max; j++) {
      printf(",  %d", results[i][j]);
    }
    printf(" }\n");
  }   

  return 0;
}
