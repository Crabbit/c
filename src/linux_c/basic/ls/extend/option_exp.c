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

//char decode_switches(int argc, char *argv[])
int main(int argc, char *argv[])
{
	int result;

	opterr = 0;

	while(( result = getopt(argc, argv, "al:R:u:T::") ) != -1 )
	{
		printf( "result = %d - %c.\n", result, result );
		switch(result)
		{
			case 'a':
				printf( "option = a, optopt = %c, optarg = %s\n.", optopt, optarg );
				break;
			case 'l':
				printf( "option = l, optopt = %c, optarg = %s\n.", optopt, optarg );
				break;
			case 'R':
				printf( "option = R, optopt = %c, optarg = %s\n.", optopt, optarg );
				break;
			case 'u':
				printf( "option = u, optopt = %c, optarg = %s\n.", optopt, optarg );
				break;
			case 'T':
				printf( "option = T, optopt = %c, optarg = %s\n.", optopt, optarg );
				break;
			case '?':
				printf( " ls : %c: invalid option.\n",optopt );
				break;
			default:
				printf( "NO option.\n" );
				break;
		}
		printf( "argv[%d] = %s.\n", optind, argv[optind] );
	}
	printf( "result = -1, optind = %d.\n", optind );
/*
	for( result = optind, result < argc, result++ )
	      printf( "------argv[%d] = %s.\n", result, argv[result] );
	for( result = 1, result < argc, result++ )
	      printf( "end------argv[%d] = %s.\n", result, argv[result] );
*/
	return EXIT_SUCCESS;
}
