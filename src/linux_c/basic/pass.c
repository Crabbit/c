/*
 * File : pass.c
 * COder: lili
 * Time : 2013.10.11
 * Description : pass < /etc/passwd
 *
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//open function
#include<fcntl.h>
//read function
#include<unistd.h>


#include<error.h>

void my_error( const char * err_string,int line )
{
	fprintf( stderr, "Line : %d \n", line );
	perror( err_string );
	exit( 1 );
}

int main( int argc, char **argv )
{
	int		FILE_FD1;
	int		FILE_FD2;

	char		*FILE_NAME1="pass";
	char		*FILE_NAME2="/etc/passwd";

	char		READ_BUF[2048];

	if(( FILE_FD1 = open( FILE_NAME1, O_RDWR | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH )) == -1 )
		my_error( "Open error.",__LINE__ );
	if(( FILE_FD2 = open( FILE_NAME2, O_RDONLY)) == -1 )
		my_error( "Open error.",__LINE__ );

	while( 1 )
	{
		if(( read( FILE_FD2, READ_BUF, 1 ) ) == 0 )
			break;
//			my_error( "Read error.",__LINE__ );

		if(( write( FILE_FD1, READ_BUF,1) ) <= 0 )
			my_error( "Write error.",__LINE__ );
	}
	close ( FILE_FD1 );
	close ( FILE_FD2 );
	return 0;
}
