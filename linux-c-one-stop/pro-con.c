#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM 8
int queue[NUM];
sem_t blank_number, product_number;

void *P1(void *arg)
{
  int p = 0;
	while (1) {
		sem_wait(&blank_number);
		queue[p] = rand() % 1000 + 1;
    printf("Produce %d\n", queue[p]);
    p = (p+1)%NUM;
    if (p == 0)
    {
      sem_post(&product_number);
    }
		sleep(rand()%5);
	}
}

void *P2(void *arg)
{
	while (1) {
    sem_wait(&product_number);
    for (int i = 0; i < NUM; i+=1)
    {
      printf("Consume %d\n", queue[i]);
      queue[i] = 0;
    }

    for (int i = 0; i < NUM; i += 1)
    {
      sem_post(&blank_number);
    }

    sleep(rand() % 5);
  }
}

int main(int argc, char *argv[])
{
	pthread_t pid, cid;

	sem_init(&blank_number, 0, NUM);
	sem_init(&product_number, 0, 0);
	pthread_create(&pid, NULL, P1, NULL);
	pthread_create(&cid, NULL, P2, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	return 0;
}
