#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

#define LOOP_TIMES 10000
sem_t S1, S2;

void *thread_worker(void*);
void critical_section(int thread_num, int i);

int main() {
    int     rtn, i;
    sem_init(&S1, 0, 1);
    sem_init(&S2, 0, 1);
    pthread_t   pthread_id = 0;

    rtn = pthread_create(&pthread_id, NULL, thread_worker, NULL);
    if (rtn != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < LOOP_TIMES; ++i) {
        sem_wait(&S1);
        sem_wait(&S2);

        sem_post(&S1);
        sem_post(&S2);
    }
    sem_destroy(&S1);
    sem_destroy(&S2);
    return 0;
}

void *thread_worker(void *p) {
    int     i;
    for (i = 0; i < LOOP_TIMES; ++i) {
        sem_wait(&S1);
        sem_wait(&S2);

        sem_post(&S1);
        sem_post(&S2);
    }
    return NULL;
}

void critical_section(int thread_num, int i) {
    printf("Thread %d: %d\n", thread_num, i);
}
