/*
 * =====================================================================================
 *
 *       Filename:  Ctrl_pro.c
 *
 *    Description:  ctrol the process 
 *
 *        Version:  1.0
 *        Created:  10/30/2013 11:02:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Crabbit ( Lili ), lili00681@gmail.com
 *        Company:  Xiyou_linux
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#define MAX_CHILD_NUMBER 10

#define SLEEP_INTERVAL 20

int proc_number = 0;

void do_something()

{
	for( ;; )
	{
		printf( "This is process No.%d and it's pid is %d\n",
					proc_number, getpid() );
//		printf( "The proc number add is %d\n", &proc_number );
		sleep( SLEEP_INTERVAL );
	}
}

int main(int argc, char *argv[])
{
	int 	child_proc_number = MAX_CHILD_NUMBER;
	int 	i, ch;
	pid_t 	child_pid;
	pid_t 	pid[10]={0};

	if( argc > 1 )
	{
		child_proc_number = atoi( argv[1] );
		child_proc_number = ( child_proc_number > 10 )?10:
			child_proc_number;
	}
	for( i = 0; i < child_proc_number; i++ )
	{
		proc_number = i;

		if(( pid[i] = fork() ) == 0 )
			do_something();
	}

	printf( "There are this process:\n" );
	for( i = 0; i < child_proc_number; i++ )
	{
		printf( "No.%d process : Pid = %d\n", i, pid[i] );
	}

	printf( "Which do you want to kill( q is mean quit. ):" );
	while( (ch = getchar()) != 'q' )
	{
		if( isdigit(ch) )
		{
			kill( ch, SIGTERM );
		}
	}
//	kill( 0, SIGTERM );
	return EXIT_SUCCESS;
}
