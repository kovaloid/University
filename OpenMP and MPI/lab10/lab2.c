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

#define SIZE 4

int main(int argc, char *argv[])
{
    int rank, size; 
    int *sendcounts;   
    int *displs;        

    int rem = (SIZE*SIZE)%size;
    int sum = 0;                
    char rec_buf[100];         

    char data[SIZE][SIZE] = {
        {'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p'}
    };

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    sendcounts = malloc(sizeof(int)*size);
    displs = malloc(sizeof(int)*size);

    int i;
    for (i = 0; i < size; i++) {
        sendcounts[i] = (SIZE*SIZE)/size;
        if (rem > 0) {
            sendcounts[i]++;
            rem--;
        }

        displs[i] = sum;
        sum += sendcounts[i];
    }

    if (0 == rank) {
        int i;
        for (i = 0; i < size; i++) {
            printf("sendcounts[%d] = %d\tdispls[%d] = %d\n", i, sendcounts[i], i, displs[i]);
        }
    }

    MPI_Scatterv(&data, sendcounts, displs, MPI_CHAR, &rec_buf, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("[%d] received: \n", rank);
    for (i = 0; i < sendcounts[rank]; i++) {
        printf("  %c", rec_buf[i]);
    }
    printf("\n\n");

    MPI_Finalize();

    free(sendcounts);
    free(displs);

    return 0;
}
