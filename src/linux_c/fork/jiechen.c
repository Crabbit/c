/*
 * =====================================================================================
 *
 *       Filename:  jiechen.c
 *
 *    Description:  jiechen
 *
 *        Version:  1.0
 *        Created:  10/30/2013 12:22:54 AM
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
	int sum = 1;

	for( i = 1; i<= 10; i++ )
	{
		sum = sum * i;
		printf( " %d! = %d\n",i,sum );
	}
	return EXIT_SUCCESS;
}

