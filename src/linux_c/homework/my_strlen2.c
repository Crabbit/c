/*
 * =====================================================================================
 *
 *       Filename:  my_strlen.c
 *
 *    Description:  测量字符串长度
 *    		注意：请将测试字符串保存在当前目录下string.txt文件中
 *    		该程序会读取其中的内容
 *    		注意：由于是读取文件中的内容，文件中如果存在换行符
 *    		则算作一个字符.
 *
 *        Version:  1.0
 *        Created:  02/04/2014 07:06:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lili, lili00681@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<error.h>

#include<time.h>

#include<fcntl.h>

#include<unistd.h>



void my_error( const char * err_string, int line )
{
	fprintf( stderr, "Line : %d \n", line );
	perror( err_string );
	exit( 1 );
}
int my_strlen( const char *str )
{
	int count = 0;
	while( *str != '\0' )
	{
		count ++;
		str++;
	}
	return count;
}

int main( int argc, char *argv[] )
{
	int 		FILE_FD;
	int 		i = 0;

	int 		length = 0;

	char 		*FILE_NAME="string.txt";

	char 		READ_BUF[1];
	char 		String[1024000];

	int 		time_start;
	int 		time_end;

	if(( FILE_FD = open( FILE_NAME, O_RDONLY )) == -1 )
	      my_error( "open error.",__LINE__ );

	while(1)
	{
		if(( read(FILE_FD, READ_BUF, 1 )) == 0 )
		{
			String[i]= '\0';
		      break;
		}

		String[i] = READ_BUF[0];
		i++;

	}

//strlen
	printf( "Start time :%d\n", (int)clock() );
	time_start = (int)clock();

	for( i = 0; i < 20; i++ )
		length = strlen( String );

	time_end = (int)clock();
	printf( "End time :%d\n", (int)clock() );

	if( time_end - time_start < 1000)
		printf( "USE time is :%d ms.\n", ( time_end - time_start )%1000 );
	else
		printf( "USE time is :%d ms.\n", ( time_end - time_start )/1000 );
	printf( "Standard strlen length is:%d\n", length);

// my strlen
	printf( "Start time :%d\n", (int)clock() );
	time_start = (int)clock();

	for( i = 0; i < 20; i++ )
		length = my_strlen( String );
	time_end = (int)clock();
	printf( "End time :%d\n", (int)clock() );

	if( time_end - time_start < 1000)
		printf( "USE time is :%d ms.\n", ( time_end - time_start )%1000 );
	else
		printf( "USE time is :%d ms.\n", ( time_end - time_start )/1000 );
	printf( "My strlen length is:%d\n", length);

	return EXIT_SUCCESS;
}
