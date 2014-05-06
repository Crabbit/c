/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  纳新面试第一题
 *
 *        Version:  1.0
 *        Created:  05/05/2014 11:38:03 PM
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

#define N sizeof(num)/sizeof(*num)
int num[] = {11, 22, 33, 44, 55, 66};

int main(int argc, char *argv[])
{
	int i;

	for( i = -1; i < N; i++ )
	      printf( "%d\n", num[i+1] );

	return EXIT_SUCCESS;
}

