/*
 * =====================================================================================
 *
 *       Filename:  pipe.c
 *
 *    Description:  管道的基本使用
 *                  注意管道只能由相关进程使用
 *                  这些相关进程的共同祖先进程创建的了管道
 *                  例外：(装备基于STREAMS的管道)
 *
 *        Version:  1.0
 *        Created:  11/26/2013 11:25:19 PM
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

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t 		RETURN_pid;
	int 		read_size;
	char 		buf_r[100];
	char 		buf_w[100];

	int 		pipe_fd[2];

	memset( buf_r, 0, 100 );

	if( pipe( pipe_fd ) < 0 )
	{
		perror( "Pipe error." );
		exit( EXIT_FAILURE );
	}

	if( ( RETURN_pid = fork()) < 0 )
	{
		perror( "Fork error." );
		exit( EXIT_FAILURE );
	}
	else
	      if( RETURN_pid == 0 )
	      {
		      printf( "Child process pid is %d\n",getpid() );
	      	close( pipe_fd[1] );
		      if( (read_size = read( pipe_fd[0], buf_r, 100 )) > 0 )
			    printf( "Child Process has read %s.\n",buf_r );
		      close( pipe_fd[0] );
		exit(0);
	      }
	      else
	      {
		      close( pipe_fd[0] );
		      printf( "Pleae input pipe string:" );
		      scanf( "%s",buf_w );
		      printf( "buf_w is :%s\n", buf_w  );
		      if( write( pipe_fd[1], buf_w, strlen(buf_w) ) != strlen(buf_w));
		      close( pipe_fd[1] );
		      waitpid( RETURN_pid, NULL, 0 );
		      exit(0);
	      }

	return EXIT_SUCCESS;
}

