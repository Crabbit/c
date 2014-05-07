/*
 * =====================================================================================
 *
 *       Filename:  5.c
 *
 *    Description:  第五题
 *
 *        Version:  1.0
 *        Created:  05/06/2014 11:47:12 PM
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

struct data {
	int a:7;
	int b:6;
	int c:5;
	int d;
}a = {0xed, 0xcd, 0xad, 0x9d};

int main(int argc, char *argv[])
{
	printf( "a = %d, b = %d, c = %d, d = %d.\n",a.a, a.b, a.c, a.d );

	return EXIT_SUCCESS;
}
