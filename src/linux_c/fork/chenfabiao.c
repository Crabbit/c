/*
 * =====================================================================================
 *
 *       Filename:  chenfabiao.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2013 12:19:15 AM
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

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	for( i = 1; i <= 9; i++ )
	{
	      for( j = 1; j <= i; j++ )
		{
			printf( "%d*%d=%d  ",j, i, j*i );
		}
	      printf( "\n" );
	}
	return EXIT_SUCCESS;
}

