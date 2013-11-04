/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/29/2013 11:58:17 PM
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

#include<error.h>

int main(int argc, char *argv[], char **environ)
{
	pid_t        	pid_1,pid_2,pid_3;
	int 		i = 0;
	char 		choice;

	for( i = 0; 1 ; i++ )
	{
		printf( "Please make your choice:\n" );
		scanf( "%c",&choice );

		if ( choice == 'q' )
		      return 0;
		if( choice == 'a' )
		{
			pid_1 = fork();
			if( pid_1 == 0 )
			{
				printf( "My pid = %d.\n", getpid() );
				printf( "My father pid = %d.\n",getppid() );
				execve( "chenfabiao", argv, environ );
				return 0;
			}
		}

		if( choice == 'b' )
		{
			pid_2 = fork();
			if( pid_2 == 0 )
			{
				printf( "My pid = %d.\n", getpid() );
				printf( "My father pid = %d.\n",getppid() );
				execve( "jiechen", argv, environ );
				return 0;
			}
		}

		if( choice == 'c' )
		{
			pid_3 = fork();
			if( pid_3 == 0 )
			{
				printf( "My pid = %d.\n", getpid() );
				printf( "My father pid = %d.\n",getppid() );
				execve( "jiafa", argv, environ );
				return 0;
			}
		}
		sleep(1);
	}
	return EXIT_SUCCESS;
}

