/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  第二题
 *
 *        Version:  1.0
 *        Created:  05/06/2014 11:19:42 PM
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

struct data3{
	double d;
	int i;
	char c;
};

union data1{
	double d;
	int i;
	char c;
};

struct data2{
	double d;
	union data1 da;
	int i;
	char c;
};
int main(int argc, char *argv[])
{
	union data1 a;
	struct data2 b;
	printf( "sizeof data1 = %d.\nsizeof data2 = %d.\n",sizeof(a), sizeof(b) );

	return EXIT_SUCCESS;
}

