#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_THREADS 100

int var_compartilhada = 0;

//pthread_mutex_t mutex_global;
sem_t semvar; // global var


void *func_thread(void *argumento) {
	int i;
	pthread_t tid = pthread_self();	
	
	for(i = 0; i < 100; i++) {
		//pthread_mutex_lock(&mutex_global);
		sem_wait(&semvar);
		var_compartilhada++;
		sem_post(&semvar);
		//pthread_mutex_unlock(&mutex_global);
	}
	printf("Worker thread %ld: var_compartilhada = %d.\n", (long)tid, var_compartilhada);
	return 0;
}

int main(int argc, char **argv) {
	int i;
	pthread_t threads[MAX_THREADS];

	//pthread_mutex_init(&mutex_global, NULL);
	sem_init(&semvar, 0, 1);

	printf("Main thread iniciada.\n");

	for(i = 0; i < MAX_THREADS; i++)
		pthread_create(&threads[i], NULL, func_thread, NULL);

	for(i = 0; i < MAX_THREADS; i++)
		pthread_join(threads[i], NULL);

	printf("Main thread: var_compartilhada = %d.\n", var_compartilhada);

	//pthread_mutex_destroy(&mutex_global);
	sem_destroy(&semvar);

	return 0;
}