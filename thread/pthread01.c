#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void *Print(void *arg) {
	pthread_t tid = pthread_self();
	printf("Nova thread criada. TID =  %u\n", (unsigned int) tid);
	pthread_exit(NULL);
}

int main() {
	pthread_t thread;
	pthread_create(&thread, NULL, Print, (void *));
	pthread_join(thread, NULL);
	pthread_exit(NULL);
}
