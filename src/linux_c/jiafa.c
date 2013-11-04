/*
 * =====================================================================================
 *
 *       Filename:  jiafa.c
 *
 *    Description:  jiafa
 *
 *        Version:  1.0
 *        Created:  10/30/2013 12:29:40 AM
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
	int sum = 0;
	for( i = 1; i <= 20; i++ )
	      sum = sum + i;
	printf( "1+2+3+...20 = %d\n",sum );
	return EXIT_SUCCESS;
}

