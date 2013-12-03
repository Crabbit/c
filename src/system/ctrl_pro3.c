/*
 * =====================================================================================
 *
 *       Filename:  ctrl_pro.c
 *
 *    Description:  thread
 *
 *        Version:  1.0
 *        Created:  11/11/2013 06:18:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lili, lili00681@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_THREAD 3

unsigned long long main_counter,counter[MAX_THREAD];
sem_t S1, S2;

void *thread_worker( void * );

int main(int argc, char *argv[])
{

	int 		i, rtn, ch;
	pthread_t 	pthread_id[MAX_THREAD] = {0};

	int 		err;
    	sem_init(&S1, 0, 1);
	sem_init(&S2, 0, 1);

	for( i = 0; i < MAX_THREAD; i++ )
	{
		err = pthread_create( &pthread_id[i], NULL, thread_worker, &i );
//		if ( err != 0 )
//		      err_quit( "Can't create thread :%s\n", strerror(err) );
		sleep(1);
	}

	do
	{
		unsigned long long sum = 0;
        sem_wait(&S1);
		for( i = 0; i < MAX_THREAD; i++ )
		{
			sum += counter[i];
			printf( "counter[%d] = %llu\n",i,counter[i] );
		}
		printf( "main counter = %llu/ sum = %llu\n",main_counter, sum );
        sem_post(&S1);
	}
	while(( ch = getchar()) != 'q' );

    sem_destroy(&S1);
    sem_destroy(&S2);
	return EXIT_SUCCESS;
}

void *thread_worker( void *p )
{
	int thread_num;

	thread_num = *(int *)p;

	for( ;; )
	{
        sem_wait(&S1);
		counter[thread_num]++;
		main_counter++;
        sem_post(&S1);
	}
}
