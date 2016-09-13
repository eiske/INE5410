#include <pthread.h>
#include <stdio.h>

void *PrintHello(void *arg) {
	long int val = (long int) arg;
	pthread_t tid = pthread_self();
	printf("Thread %u: Hello! arg = %ld\n", (unsigned int)tid, val);
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	pthread_t thread;
	long int arg = 123;
	pthread_create(&thread, NULL, PrintHello, (void *)arg);
	pthread_join(thread, NULL);
	pthread_exit(NULL);
}