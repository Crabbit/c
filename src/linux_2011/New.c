/*
 * Copy right (c) Xiyou linux.
 * This software is test the command- od to open binary file.
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<sys/stat.h>

void my_err( const char *err_string,int line )
{
	fprintf( stderr,"line : %d .\n",line );
	perror( err_string );
	exit( 1 );
}

int main()
{
	int		FILE_fd;
	char		*FILE_name;
	char		*STRR;

	FILE_name = "Info";
	STRR = "Hello~ Boy/girl.You can do anything in the server within the power of";

	if( ( FILE_fd = open( FILE_name, O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR |  S_IROTH )) == -1 )
		my_err( "Create file",__LINE__ );

	if( write( FILE_fd, STRR, strlen( STRR )  ) == -1 )
		my_err( "Write",__LINE__ );

	close ( FILE_fd );

	return 0;
}
