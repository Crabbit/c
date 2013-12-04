/*
 *Copyright (c) Xiyou_linux
 *All rights reserved.
 *
 *File		:	bianma.c
 *Time		:	2013.4.23
 *Editor	:	lili
 *Email		:	lili00681@gmail.com
 *Thanks	:	Unix program
 *
 *
 * This program is for hexadecimal to jpg file.
 *
 * */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<errno.h>

#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int caculate( char word );

void my_err( const char *err_string, int line )
{
	fprintf( stderr, "line : %d .\n", line );
	perror( err_string );
	exit( 1 );
}

int main( int args, char *argv[] )
{
	char		*FILE_R_NAME;
	char		*FILE_W_NAME;
	int		FILE_R_FD;
	int		FILE_W_FD;

	char		Read_buf[2];

	int		test;

	FILE_R_NAME = argv[1];
	FILE_W_NAME = "out.jpg" ;

	if( ( FILE_R_FD = open( FILE_R_NAME, O_RDONLY )) == -1 )
		my_err( "Open Read failed",__LINE__ );

	if( ( FILE_W_FD = open( FILE_W_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH )) == -1 )
		my_err( "Open write failed",__LINE__ );

	for ( ; ( test = read( FILE_R_FD, Read_buf, 2 )) != 0 ; )
	{
		char num;
		num = caculate( Read_buf[0] )*16 + caculate( Read_buf[1] );
		printf( "%c",num );

		if( write( FILE_W_FD, &num, 1 ) == -1 )
			my_err( "Write error.",__LINE__ );
	}

	close( FILE_R_FD );
	close( FILE_W_FD );

	return 0;
}

int caculate( char word )
{
	switch( word )
	{
		case '0':	return 0;break; 
		case '1':	return 1;break; 
		case '2':	return 2;break; 
		case '3':	return 3;break; 
		case '4':	return 4;break; 
		case '5':	return 5;break; 
		case '6':	return 6;break; 
		case '7':	return 7;break; 
		case '8':	return 8;break; 
		case '9':	return 9;break; 
		case 'A':	return 10;break; 
		case 'B':	return 11;break; 
		case 'C':	return 12;break; 
		case 'D':	return 13;break; 
		case 'E':	return 14;break; 
		case 'F':	return 15;break; 
		default : printf( "word error.\n" );
	}
}
