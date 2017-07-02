 /* Произведение двух матриц в топологии "трехмерная решетка" компьютеров
 */
/* В примере предполагается, что количество строк и столбцов матрицы A
 * и количество строк и столбцов матрицы B делятся без остатка на количество
 * компьютеров в системе.
 * В данном примере задачу запускаем на 8-х компьютерах и на решетке 2х2х2.
 */
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<sys/time.h>

/* NUM_DIMS - размер декартовой топологии. "трехмерная решетка" P0xP1xP2 */
#define NUM_DIMS 3
#define P0 3
#define P1 3
#define P2 3

/* Задаем размеры матриц A = MxN, B = NxK и C = MxK (Эти размеры значимы в ветви 0) */
#define M 500
#define N 500
#define K 500

#define A(i,j) A[N*i+j]
#define B(i,j) B[K*i+j]
#define C(i,j) C[K*i+j]
#define C1(i,j) C1[K*i+j]


/* Подпрограмма, осуществляющая перемножение матриц */
int PMATMAT_3(n, A, B, C, p, comm)
	/* Аргументы A, B, C, n, p значимы только в ветви 0 */
	int *n;                 /* Размеры исходных матриц */     
	double *A, *B, *C;      /* Исходные матрицы: A[n[0]][n[1]], B[n[1]][n[2]], C[n[0]][n[2]]; */

	/* Данные размеров решетки процессов. p[i] соответствует n[i] и произведение 3-х измерений эквивалентно размеру группы  comm */
	int *p;

	/* Коммуникатор для процессов, умножающих матрицу на матрицу */
	MPI_Comm comm;
{
	/* Далее все описываемые переменные значимы во всех ветвях, в том числе и ветви 0 */
	double *AA, *BB, *CC, *CC1;    	/* Локальные подматрицы (полосы) */
	int nn[3];                 	 	/* Размеры полос в A и B и подматриц CC в C */

	/* Коммуникаторы для 3D решетки, для подрешеток, и копии comm */
	int coords[3];           /* Декартовы координаты */
	int rank;                /* Ранг процесса (ветви) */

	/* Смещения и размеры для операций scatter/gather */
	int *dispa, *dispb, *dispc, *counta, *countb, *countc;

	/* Переменные и массивы для создаваемых типов данных */
	MPI_Datatype typea, typeb, typec, types[2];
	int periods[3], remains[3];
	MPI_Comm comm_3D, comm_2D[3], comm_1D[3], pcomm;
	int i, j, k, blen[2];
	MPI_Comm_dup(comm, &pcomm);                /* Копия коммуникатора comm */
	
	MPI_Aint sizeofdouble, disp[2];
	/* Передача параметров n[3] и p[3] */
	MPI_Bcast(n, 3, MPI_INT, 0, pcomm);
	MPI_Bcast(p, 3, MPI_INT, 0, pcomm);

	/* Создание 3D решетки процессов */
	for(i = 0; i < 3; i++) {
		periods[i] = 0;
	}
	MPI_Cart_create(pcomm, 3, p, periods, 0, &comm_3D);
	
	//printf("%s \n", &comm_3D);
	/* Нахождение ранга и декартовых координат */
	MPI_Comm_rank(comm_3D, &rank);
	MPI_Cart_coords(comm_3D, rank, 3, coords);

	/* Получение коммуникаторов для подрешеток размерности 2D */
	for(i = 0; i < 3; i++) { 
		for(j = 0; j < 3; j++)
			remains[j] = (i != j);
		MPI_Cart_sub(comm_3D, remains, &comm_2D[i]);
	}

	/* Получение коммуникаторов для подрешеток размерности 1D */
	for(i = 0; i < 3; i++) { 
		for(j = 0; j < 3; j++)
			remains[j] = (i == j);
		MPI_Cart_sub(comm_3D, remains, &comm_1D[i]);
	}

	/* Выделение памяти для подматриц */
	for(i = 0; i < 3; i++)
		nn[i] = n[i]/p[i];

	#define AA(i,j) AA[nn[1]*i+j]
	#define BB(i,j) BB[nn[2]*i+j]
	#define CC(i,j) CC[nn[2]*i+j]

	AA = (double *)malloc(nn[0] * nn[1] * sizeof(double));
	BB = (double *)malloc(nn[1] * nn[2] * sizeof(double));
	CC = (double *)malloc(nn[0] * nn[2] * sizeof(double));

	/* Работа нулевой ветви */
	if(rank == 0) {
	/* Создание типа данных для подматриц в A */
		MPI_Type_vector(nn[0], nn[1], n[1], MPI_DOUBLE, &types[0]);
		/* и коректировка размеров подстрок */
		MPI_Type_extent(MPI_DOUBLE, &sizeofdouble);
		blen[0] = 1;
		blen[1] = 1;
		disp[0] = 0;
		disp[1] = sizeofdouble * nn[1];
		types[1] = MPI_UB;
		MPI_Type_struct(2, blen, disp, types, &typea);
		MPI_Type_commit(&typea);
		/* Нахождение смещений и размеров подматриц в A.
		* Подматрицы в A упорядочены аналогично упорядочению процессов в решетке. */
		dispa = (int *)malloc(p[0]*p[1] * sizeof(int));
		counta = (int *)malloc(p[0]*p[1] * sizeof(int));
		for(j = 0; j < p[0]; j++)
			for(i = 0; i < p[1]; i++) { 
				dispa[j*p[1]+i] = (j*p[1]*nn[0] +i);
				counta[j*p[1]+i] = 1;
			}
		 /* Тоже самое для массива B */
		MPI_Type_vector(nn[1], nn[2], n[2], MPI_DOUBLE, &types[0]);
		disp[1] = sizeofdouble*nn[2];
		MPI_Type_struct(2,blen,disp,types,&typeb);
		MPI_Type_commit(&typeb);
	   	dispb = (int *)malloc(p[1]*p[2] * sizeof(int));
		countb = (int *)malloc(p[1]*p[2] * sizeof(int));
		for(j = 0; j < p[1]; j++)
			for(i = 0; i < p[2]; i++) { 
				dispb[j*p[2]+i] = (j*p[2]*nn[1] +i);
		        countb[j*p[2]+i] = 1;
			}

		/* Тоже самое для массива C */
		MPI_Type_vector(nn[0], nn[2], n[2], MPI_DOUBLE, &types[0]);
		disp[1] = sizeofdouble*nn[2];
		MPI_Type_struct(2, blen, disp, types, &typec);
		MPI_Type_commit(&typec);
		dispc = (int *)malloc(p[0]*p[2] * sizeof(int));
		countc = (int *)malloc(p[0]*p[2] * sizeof(int));
		for(j = 0; j < p[0]; j++)
			for(i = 0; i < p[2]; i++) { 
				dispc[j*p[2]+i] = (j*p[2]*nn[0] +i);
		        countc[j*p[2]+i] = 1;
		    }   
	}      /* Нулевая ветвь завершает подготовительную работу */

	/* Вычисления. Этапы представлены на рис. 2.6 в главе 2. */
	/* 1. Нулевая ветвь передает (scatter) горизонтальные полосы матрицы A по x координате */
	if(coords[2] == 0)
		MPI_Scatterv(A, counta, dispa, typea, AA, nn[0]*nn[1], MPI_DOUBLE, 0, comm_2D[2]);

	/* 2. Нулевая ветвь передает (scatter) вертикальные полосы матрицы B по y координате */
	if(coords[0] == 0)	
		MPI_Scatterv(B, countb, dispb, typeb, BB, nn[1]*nn[2], MPI_DOUBLE, 0, comm_2D[0]);

	/* 3. Рассылка (broadcast) подматриц AA в измерении z */
	MPI_Bcast(AA, nn[0]*nn[1], MPI_DOUBLE, 0, comm_1D[2]);

	/* 4. Рассылка (broadcast) подматриц BB в измерении x */
	MPI_Bcast(BB, nn[1]*nn[2], MPI_DOUBLE, 0, comm_1D[0]);

	/* 5. Вычисление всеми ветвями подматриц CC */
	for(i = 0; i < nn[0]; i++)
		for(j = 0; j < nn[2]; j++) { 
			CC(i,j) = 0;
			for(k = 0; k < nn[1]; k++)
		        CC(i,j) = CC(i,j) + AA(i,k) * BB(k,j);

		}

	/* 6. Сбор подматриц CC в измерении y */
	/* Редукция подматриц CC вначале осуществляется "в плоскости" */
	CC1 = (double *)malloc(nn[0] * nn[2] * sizeof(double));
	MPI_Reduce(CC, CC1, nn[0]*nn[2], MPI_DOUBLE, MPI_SUM, 0, comm_1D[1]);

	/* 7. Сбор результатов из плоскости (x,0,z) в узел 0 */
	if(coords[1] == 0)
		MPI_Gatherv(CC1, nn[0]*nn[2], MPI_DOUBLE, C, countc, dispc, typec, 0, comm_2D[1]);

	/* Освобождение памяти всеми ветвями и завершение подпрограммы */
	free(AA);
	free(BB);
	free(CC);
	free(CC1);
	MPI_Comm_free(&pcomm);
	MPI_Comm_free(&comm_3D);
	for(i = 0; i < 3; i++) { 
		MPI_Comm_free(&comm_2D[i]);
		MPI_Comm_free(&comm_1D[i]);
	}
	if(rank == 0) { 
		free(counta);
		free(countb);
		free(countc);
		free(dispa);
		free(dispb);
		free(dispc);
		MPI_Type_free(&typea);
		MPI_Type_free(&typeb);
		MPI_Type_free(&typec);
		MPI_Type_free(&types[0]);
	}
	return 0;
}

/* Главная программа */

int main(int argc, char **argv) {
	double *A, *B, *C;
    int size, MyP, n[3], p[3], i, j, k;
    int dims[NUM_DIMS], periods[NUM_DIMS];
    int reorder = 0;
    struct timeval tv1, tv2;        /* Для засечения времени */
    int dt1;
    MPI_Comm comm;

  	/* Инициализация библиотеки MPI */
    MPI_Init(&argc, &argv);
	/* Каждая ветвь узнает количество задач в стартовавшем приложении */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

 	/* и свой собственный номер (ранг) */
    MPI_Comm_rank(MPI_COMM_WORLD, &MyP);

	/* Обнуляем массив dims и заполняем массив periods для топологии "трехмерная решетка" */
    for(i = 0; i < NUM_DIMS; i++) { 
		dims[i] = 0; 
		periods[i] = 0; 
	}
	/* Заполняем массив dims, где указываются размеры трехмерной решетки */
    MPI_Dims_create(size, NUM_DIMS, dims);

 	/* Создаем топологию "трехмерная решетка" с communicator(ом) comm */

    MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &comm);

 	/* Задаем размеры матриц и размеры трехмерной решетки компьютеров */
    n[0] = M;
    n[1] = N;
    n[2] = K;
    p[0] = P0;
    p[1] = P1;
    p[2] = P2;
	
	/* В первой ветви выделяем в памяти место для исходных матриц */
    if(MyP == 0) { 
		A = (double *)malloc(n[0] * n[1] * sizeof(double));
        B = (double *)malloc(n[1] * n[2] * sizeof(double));
        C = (double *)malloc(n[0] * n[2] * sizeof(double));
     	srand(time(NULL));
		/* Ветвь 0 генерирует исходные матрицы A и B, матрицу C обнуляет */
        for(i = 0; i < M; i++)
          	for(j = 0; j < N; j++) {
            	A(i,j) = 1+rand()%100;
				//printf("a=%f \n", A(i, j));
			}
        for(j = 0; j < N; j++)
          	for(k = 0; k < K; k++) {
            	B(j,k) = 1+rand()%100;
				//printf("b=%f \n", B(j, k));
			}
        for(i = 0; i < M; i++)
          	for(j = 0; j < K; j++)
            	C(i,j) = 0.0;
	} /* Подготовка матриц ветвью 0 завершина */
	
	/* Каждая ветвь засекает начало умножения матриц */
    gettimeofday(&tv1, (struct timezone*)0);
    
	/* Все ветви вызывают функцию перемножения матриц */
    PMATMAT_3(n, A, B, C, p, comm);

 	/* Умножение завершено. Каждая ветвь умножила свою полосу строк матрицы A на полосу столбцов матрицы B. Результат находится в нулевой ветви.
  	* Засекаем время и результат печатаем */
	gettimeofday(&tv2, (struct timezone*)0);
    dt1 = (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;
    printf("MyP = %d Time = %d\n", MyP, dt1);

 	/* Для контроля ветвь 0 печатает результат */
    /*
	if(MyP == 0) { 
		for(i = 0; i < M; i++) { 
			for(j = 0; j < K; j++)
            	printf("%3.1f  ", C(i,j));
          	printf("\n");
         }
	}
	*/
	/* Все ветви завершают системные процессы, связанные с топологией comm и завершаю выполнение программы */
    if(MyP == 0) { 
		free(A);
        free(B);
        free(C);
    }
    MPI_Comm_free(&comm);
    MPI_Finalize();
    return(0);
}

 
