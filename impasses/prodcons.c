#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS 2
#define N 10

sem_t cheio, vazio, lock_prod, lock_cons, lock_count;
int buffer[N], i = 0, f = 0, count = 0;

int produz()
{
  //sleep(1);
  int ret = rand() % N;
  sem_wait(&lock_count);
  count++;
  sem_post(&lock_count);
  printf("Thread %lu -> Produziu: %d (buffer %d/%d)\n", (unsigned long) pthread_self(), ret, count, N);
  return ret;
}

void consome(int value)
{
  //sleep(2);
  sem_wait(&lock_count);
  count--;
  sem_post(&lock_count);
  printf("Thread %lu -> Consumiu: %d (buffer %d/%d)\n", (unsigned long) pthread_self(), value, count, N);
}

void* produtor(void *arg)
{
  while(1)
  {
    sem_wait(&vazio);
    sem_wait(&lock_prod);
    f = (f + 1) % N;
    buffer[f] = produz();
    sem_post(&lock_prod);
    sem_post(&cheio);
  }
  pthread_exit(NULL);
}

void* consumidor(void *arg)
{
  while (1)
  {
    sem_wait(&cheio);
    sem_wait(&lock_cons);
    i = (i + 1) % N;
    consome(buffer[i]);
    sem_post(&lock_cons);
    sem_post(&vazio);
  }
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  int i;
  pthread_t threads[N];

  sem_init(&cheio, 0, 0);
  sem_init(&lock_prod, 0, 1);
  sem_init(&lock_cons, 0, 1);
  sem_init(&lock_count, 0, 1);
  sem_init(&vazio, 0, N);
  srand(time(NULL));

  for(i=0; i < THREADS; i++) {
    if(i%2 == 0)
      pthread_create(&threads[i], NULL, produtor, NULL);
    else
      pthread_create(&threads[i], NULL, consumidor, NULL);
  }
  
  for(i=0; i < THREADS; i++)
    pthread_join(threads[i], NULL);

  sem_destroy(&cheio);
  sem_destroy(&vazio);
  sem_destroy(&lock_prod);
  sem_destroy(&lock_cons);
  sem_destroy(&lock_count);

  return 0;
}
