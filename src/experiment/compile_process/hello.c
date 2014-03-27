/*
 * =====================================================================================
 *
 *       Filename:  helloworld.c
 *
 *    Description:  gcc实验
 *
 *        Version:  1.0
 *        Created:  03/25/2014 11:03:52 PM
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

#include "print.h"

int main(int argc, char *argv[])
{
	char *name="lili";

	printf( "Hello %s.\n", name );
	print_lili();
	print_cici();

	return EXIT_SUCCESS;
}


