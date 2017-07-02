/*
6. Первая задача про деньги. Десять бухгалтеров сводят годовой ба-
ланс. Каждый из них отвечает за свою сторону жизни предприятия – зарпла-
ту, материальные расходы и т.п., и точно знает, сколько доходов и расходов
числится за ним. Бухгалтера заполняют баланс по очереди – сперва первый
из них заполняет свой раздел, затем это делает второй и т.д. В конце концов
все попадает на стол главному бухгалтеру и он объявляет результат и везет
отчет в налоговую инспекцию. Написать программу, моделирующую пове-
дение бухгалтеров, используя метод передачи информации «точка-точка».
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sendBalance(int rank, int income, int expense) {
  srand(time(NULL) + rank);
  income = rand() % 1000 + 500;
  expense = rand() % 800 + 100;
  MPI_Send(&income, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  MPI_Send(&expense, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
  printf("[%d] Accountant send income = %d and expense = %d to next [%d]\n", rank, income, expense, rank + 1);
}

int main(int argc, char* argv[]) {
  int rank, size;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int income = 0;
  int expense = 0;

  if (rank == 0) {
    sendBalance(rank, income, expense);
  } else if (rank > 0 && rank < 10) {
    MPI_Recv(&income, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&expense, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    sendBalance(rank, income, expense);
  } else if (rank == 10) {
    MPI_Recv(&income, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&expense, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("General accountant received income = %d and expense = %d\n", income, expense);
    printf("Total balance = %d\n", income - expense);
  }
  
  MPI_Finalize();
  return 0;
}
