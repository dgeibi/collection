#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM 5
pthread_mutex_t chopsticks[NUM];

void *philosopher(void *arg)
{
  const char *args = (const char *)arg;

  char id = args[0];
  char d1 = args[1];
  char d2 = args[2];
  int o1 = d1 - '0' - 1;
  int o2 = d2 - '0' - 1;
  pthread_mutex_t *left = chopsticks + o1;
  pthread_mutex_t *right = chopsticks + o2;

  while (1)
  {
    usleep(rand() % 10);
    if (pthread_mutex_trylock(left) != 0)
    {
      continue;
    }
    printf("Philosopher %c fetches chopstick %c\n", id, d1);

    if (pthread_mutex_trylock(right) != 0)
    {
      pthread_mutex_unlock(left);
      printf("Philosopher %c gives up chopstick %c\n", id, d1);
      continue;
    }

    printf("Philosopher %c fetches chopstick %c\n", id, d2);
    usleep(rand() % 10);

    printf("Philosopher %c releases chopstick %c %c\n", id, d1, d2);
    pthread_mutex_unlock(left);
    pthread_mutex_unlock(right);
  }
}

pthread_mutex_t *make_mutex(pthread_mutex_t *mutex)
{
  int n = pthread_mutex_init(mutex, NULL);
  if (n != 0)
  {
    perror("make_lock failed");
    exit(1);
  }
  return mutex;
}

int main(int argc, char *argv[])
{
  pthread_t a, b, c, d, e;

  for (int i = 0; i < NUM; i += 1)
  {
    make_mutex(chopsticks + i);
  }
  pthread_create(&a, NULL, philosopher, "a51");
  pthread_create(&b, NULL, philosopher, "b12");
  pthread_create(&c, NULL, philosopher, "c23");
  pthread_create(&d, NULL, philosopher, "d34");
  pthread_create(&e, NULL, philosopher, "e45");
  pthread_join(a, NULL);
  pthread_join(b, NULL);
  pthread_join(c, NULL);
  pthread_join(d, NULL);
  pthread_join(e, NULL);
  return 0;
}
