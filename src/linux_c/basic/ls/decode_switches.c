/*
 * =====================================================================================
 *
 *       Filename:  decode_switches.c
 *
 *    Description:  处理参数
 *
 *        Version:  1.0
 *        Created:  05/19/2014 08:12:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lili, lili00681@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//处理用户参数
char decode_switches(int argc, char *argv[])
{
	int result;

	opterr = 0;

	while(( result = getopt(argc, argv, "al:R:u:") ) != -1 )
	{
		printf( "result = %d - %c.\n", result, result );
		switch(result)
		{
			case 'a':
				printf( "option = a\n." );
				break;
			case 'l':
				printf( "option = l, optarg = %s\n.", optarg );
				break;
			case 'R':
				printf( "option = R, optarg = %s\n.", optarg );
				break;
			case 'u':
				printf( "option = u, optarg = %s\n.", optarg );
				break;
			//处理未定义的参数
			case '?':
				printf( "ls: %c: invalid option\n", optopt );
				printf( "ls: usage: ls [-a|-l|-R|-u] [file|dir]" );
				break;
			//不带参数
			default:
				printf( "NO option.\n" );
				break;
		}
	}
	return EXIT_SUCCESS;
}
