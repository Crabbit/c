/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  第四题
 *
 *        Version:  1.0
 *        Created:  05/06/2014 11:46:00 PM
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
	char array[] = "xiyoulinux!";

	printf( "strlen : %d, sizeof: %d.\n", strlen(array), sizeof(array));

	return EXIT_SUCCESS;
}

