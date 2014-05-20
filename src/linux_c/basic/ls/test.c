/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  aa
 *
 *        Version:  1.0
 *        Created:  05/20/2014 12:50:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lili, lili00681@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct haha
{
	int a;
	int b;
}test;

int comp( const void *a, const void *b )
{
	return (*(test *)a).b < (*(test *)b).b ? 1: 0;
}

int main(int argc, char *argv[])
{
	int i = 0;
	int x = 0;

	test *array;

	printf( "Please input x:" );
	scanf( "%d",&x );

	//array = (int *)malloc( x * sizeof(int) );
	array = (test *)realloc( array , i+1 * sizeof(test) );

	for( i = 0; i < x; i++ )
	{
		array = ( test *)realloc( array , (i+1) * sizeof(test) );
		array[i].a = 10 - i;
		array[i].b = i*10;
		printf( "a = %d  b = %d\n",array[i].a, array[i].b );
	}
	//qsort( array, x, sizeof(array[0]), comp );

	printf( "\n" );
	for( i = 0; i < x; i++ )
		printf( "a = %d  b = %d\n",array[i].a, array[i].b );

	printf( "\n" );

	return EXIT_SUCCESS;
}

