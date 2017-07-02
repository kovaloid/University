#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_1 6
#define SIZE_2 4
#define SIZE_3 5
#define SIZE_4 3

int main(int argc, char** argv)
{
  int threads = 5;
  if (argc > 1) {
    threads = atoi(argv[1]);
  }
  printf("Number of threads: %d\n", threads);

  int a1[SIZE_1] = { 1, 2, 3, 4, 5, 6 };
  int a2[SIZE_2] = { 7, 8, 9, 10 };
  int a3[SIZE_3] = { 11, 12, 13, 14, 15 };
  int a4[SIZE_4] = { 16, 17, 18 };
  int i, j;

  printf("ARRAYS: \n");
  for (i = 0; i < SIZE_1; i++) {
    printf("\t%d", a1[i]);
  }
  printf("\n");
  for (i = 0; i < SIZE_2; i++) {
    printf("\t%d", a2[i]);
  }
  printf("\n");
  for (i = 0; i < SIZE_3; i++) {
    printf("\t%d", a3[i]);
  }
  printf("\n");
  for (i = 0; i < SIZE_4; i++) {
    printf("\t%d", a4[i]);
  }
  printf("\n");

  int res1[SIZE_1 * SIZE_2][2];
  int res2[SIZE_3 * SIZE_4][2];
  int res[SIZE_1 * SIZE_2 * SIZE_3 * SIZE_4][4];

  #pragma omp parallel for shared(res1) private(i, j) num_threads(SIZE_1)
  for (i = 0; i < SIZE_1; i++) {
    for (j = 0; j < SIZE_2; j++) {
      res1[i*SIZE_2 + j][0] = a1[i];
      res1[i*SIZE_2 + j][1] = a2[j];
    }
  }

  #pragma omp parallel for shared(res2) private(i, j) num_threads(SIZE_3)
  for (i = 0; i < SIZE_3; i++) {
    for (j = 0; j < SIZE_4; j++) {
      res2[i*SIZE_4 + j][0] = a3[i];
      res2[i*SIZE_4 + j][1] = a4[j];
    }
  }

  printf("\n\nRESULT: \n");
  for(i = 0; i < SIZE_1 * SIZE_2; i++) {
    for(j = 0; j < SIZE_3 * SIZE_4; j++) {
      printf("{ %d,  %d,  %d,  %d }\n", res1[i][0], res1[i][1], res2[j][0], res2[j][1]);
    }
  } 

  return 0;
}
