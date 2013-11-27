/*
 * File : mkdir.c
 * COder: lili
 * Time : 2013.10.11
 * Description : creat a directory
 *
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/stat.h>

#include<error.h>

void my_error( const char * err_string,int line )
{
	fprintf( stderr, "Line : %d \n", line );
	perror( err_string );
	exit( 1 );
}

int main( int argc, char **argv )
{

	if( argc == 1 )
	{
		printf( "Usage : mkdir dir1 dir2 dir3 ..." );
		exit( 1 );
	}

	int		PATHNAME = 1;

	printf( "argc=%d\n",argc );
	printf( "%s\n",argv[PATHNAME] );
	for( ; argc != 1 ; argc -= 1, PATHNAME += 1)
	{
		if(( mkdir( argv[PATHNAME], S_IXUSR | S_IXGRP | S_IXOTH )) == -1 )
			my_error( "Mmkdir",__LINE__ );
	}
	
	return 0;
}
