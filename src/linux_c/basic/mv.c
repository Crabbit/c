/*
 * File : mv.c
 * COder: lili
 * Time : 2013.10.11
 * Description : about mv command study
 *
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<error.h>

#include<unistd.h>
#include<fcntl.h>

void my_error( const char * err_string,int line )
{
	fprintf( stderr, "Line : %d \n", line );
	perror( err_string );
	exit( 1 );
}

int cp_delete( char *filename1, char *filename2 )
{
	int        FILE_FD1;
	int        FILE_FD2;

	char       READ_BUF[4096];
	
	if(( FILE_FD1 = open( filename2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1  )
	      	my_error( "Open file 1 error.",__LINE__ );
	if(( FILE_FD2 = open( filename1, O_RDONLY )) == -1 )
	      	my_error( "Open file 2 error.",__LINE__ );

	while( 1 )
	{
		if(( read( FILE_FD2, READ_BUF, 1 )) == 0 )
		      break;

		if(( write( FILE_FD1, READ_BUF,1 )) <= 0 )
		      my_error( "Write error",__LINE__ );
	}

	close( FILE_FD1 );
	close( FILE_FD2 );

	remove( filename1 );
	return 0;
}

int main( int argc, char **argv )
{

// for count
	int 		i;
// flag = 1 -- file
// flag = 0 -- directory
	int 		flag = 1;
// \n flag
	int             N_flag = 0;
// new directory
 	char            NEW_dir[32];
// old argv[2] name length
	int             OLD_path_length = 0;
// new file name length
	int             NEW_file_length = 0;
// new file name
	char            NEW_file_name[32];

	if( argc > 3 )
	{
		printf( "Usage : mv file_oldname file_newname" );
		return 0;
	}

	OLD_path_length = strlen( argv[2] );

	for( i = 0; (OLD_path_length - i) != 0 ; i++ )
	{
		if( flag == 1 && argv[2][OLD_path_length-i-1] == '/' )
		      flag = 0;
		if( flag == 1 )
		      NEW_file_length += 1;

		if( N_flag == 0 && flag == 0 )
		{
			N_flag = 1;
			NEW_dir[OLD_path_length-i] = '\n';
		}
		if( flag == 0 )
			NEW_dir[OLD_path_length-1-i] = argv[2][OLD_path_length-i-1]; 
	}

	for( i = 0; i != NEW_file_length; i++ )
	{
		if( N_flag == 0 )
		{
			N_flag = 1;
			NEW_file_name[NEW_file_length] = '\n';
		}
		else
			NEW_file_name[NEW_file_length-1-i] = argv[2][OLD_path_length-1-i];
	}

	printf( "The new file name is %s \n",NEW_file_name );
	printf( "The new file path is %s \n",NEW_dir );

	if( flag == 1 )
		if ( (rename( argv[1], argv[2] )) == -1 )
		{
			my_error( "Rename error",__LINE__ );
		}
	if( flag == 0 )
	      cp_delete( argv[1], argv[2] );
	return 0;
}
