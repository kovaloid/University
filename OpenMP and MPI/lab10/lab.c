/*
7. Реализовать рассылку массива значений на n процессов с помощью
двухточечных обменов по принципу: каждому процессу отправляется зара-
нее заданное число значений. Эффективность реализации сравнить с функци-
ей MPI_Scatterv().
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 16
#define BLOCK_SIZE 2

int main(int argc, char* argv[]) {
  int rank, size;

  char data[SIZE] = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p'
    };

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  char income[BLOCK_SIZE];

  if (rank == 0) {
    int i;
    printf("source:\n");
    for (i = 0; i < SIZE; i++) {
      printf("  %c", data[i]);
    }
    printf("\n\n");
    for (i = 0; i < 8; i++) {
      MPI_Send(&data[i*BLOCK_SIZE], BLOCK_SIZE, MPI_CHAR, i + 1 , 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(&income, BLOCK_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("[%d] received:\n", rank);
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
      printf("  %c", income[i]);
    }
    printf("\n\n");
  }

  MPI_Finalize();
  return 0;
}
