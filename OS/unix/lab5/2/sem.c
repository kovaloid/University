#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NBUFF 5
int nitems = 30;

struct {
	int buff[NBUFF];
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nempty, nstored;
} shared;

void *produce(void *), *consume(void *);

int main(int argc, char **argv)
{
	pthread_t tid_produce, tid_consume;

	pthread_cond_init(&shared.cond,NULL);
	pthread_mutex_init(&shared.mutex,NULL);

	shared.nempty = NBUFF;
	shared.nstored = 0;

	pthread_create(&tid_produce, NULL, produce, NULL);
	pthread_create(&tid_consume, NULL, consume, NULL);

	pthread_join(tid_produce, NULL);
	pthread_join(tid_consume, NULL);

	pthread_mutex_destroy(&shared.mutex);
	pthread_cond_destroy(&shared.cond);

	exit(0);
}

void *produce(void *arg)
{
	puts("[producer] thread started");
	int i;

	for(i=0; i<nitems; i++)
	{
		usleep(200000);

		pthread_mutex_lock(&shared.mutex);

		shared.buff[shared.nstored] = i;

		printf("[producer] put in buffer[%d] = %d\n",shared.nstored,shared.buff[shared.nstored]);
		shared.nempty--;
		shared.nstored++;
		if (shared.nstored >= NBUFF)
		{
			puts("[producer] buffer is maximum");
			pthread_cond_signal(&shared.cond);
		}

		pthread_mutex_unlock(&shared.mutex);
	}
	return(NULL);
}

void *consume(void *arg)
{
	puts("[consumer] thread started");
	int i,j;

	for(i=0; i<nitems; i++)
	{
		pthread_mutex_lock(&shared.mutex);

		while (shared.nstored < NBUFF)
		{
			pthread_cond_wait(&shared.cond,&shared.mutex);
		}

		printf("[consumer] buffer is maximum\n");
		printf("[consumer] out of buffer ");

		for(j=0; j<NBUFF; j++)
			printf("[%d]=%d ",j,shared.buff[j]);

		printf("\n");
		shared.nstored = 0;
		shared.nempty = NBUFF;
		pthread_mutex_unlock(&shared.mutex);
	}
	return(NULL);
}
