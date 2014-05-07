/*
 * =====================================================================================
 *
 *       Filename:  7.c
 *
 *    Description:  第七题
 *
 *        Version:  1.0
 *        Created:  05/06/2014 11:59:21 PM
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

int main(int argc, char *argv[])
{
	int a = 1;
	int b = 2;
	switch (a, 2)
	{
		++b;
		case 1:
			printf( "b is %d.\n", ++b );
			break;
		default:
			printf( "b is %d.\n", --b );
			break;
	}

	return EXIT_SUCCESS;
}

