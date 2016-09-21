#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 10

int var_compartilhada = 0;

char buffer[N];
sem_t full; // cheio = 0;
sem_t empty; // vazio = n;

void *producer(void *argumento) {
	for(int i = 0; ; i = (i + 1) % N) {
		//pthread_mutex_lock(&mutex_global);
		sem_wait(&empty);
		buffer[i] = i;
		sem_post(&full);
		//pthread_mutex_unlock(&mutex_global);
		
	}
	//printf("Worker thread %ld: var_compartilhada = %d.\n", (long)tid, var_compartilhada);
	return 0;
}

void *consumer(void *argumento) {
	for(int i = 0; ; i = (i + 1) % N) {
		//pthread_mutex_lock(&mutex_global);
		sem_wait(&full);
		printf("%d", buffer[i]);
		sem_post(&empty);
		//pthread_mutex_unlock(&mutex_global);
		
	}
	//printf("Worker thread %ld: var_compartilhada = %d.\n", (long)tid, var_compartilhada);
	return 0;
}

int main() {
  pthread_t producer_thread;
  pthread_t consumer_thread;

  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  sem_destroy(&full);
  sem_destroy(&empty);

  return 0;

  }
