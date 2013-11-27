//The program is just for change the file owner


#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

//The funcation : int chown ( const char *path, uid_t owner, gid_t group )
//The funcation : int fchown ( int fd, uid_t owner, gid_t group )
//The funcation : lchown ( const char *path, udi_t owner, gid_t group )

//The funcation : open ( const char *pathname, int flags )
//The funcation : open ( const char *pathname, int flags, mode_t mode )

void my_err( const char * err_string, int line )
{
	fprintf( stderr,"line : %d",line );
	perror( err_string );
	exit( 1 );
}

int main( int argc, char **argv )
{
	int fd;
	int ret;
	uid_t own;
	gid_t grp;
	char filename;

	if( argc != 3 && argc != 4)
	{
		printf("Usage : chown <filename> [user] [group]\n");
		exit( 1 );
	}

	if( (fd = open( argv[ 1 ], O_RDONLY ) ) == -1 )	
		my_err( "open",__LINE__ );
	
	if( argc == 3 )
	{
		own = atoi( argv[2] );
		if( ( ret = fchown( fd, own, -1 ) ) == -1 )
			my_err( "fchown",__LINE__ );
		else
			printf( "Change successful.\n" );
	}
	
	if( argc == 4 )
	{
		own = atoi( argv[2] );
		grp = atoi( argv[3] );
		if( ( ret = fchown( fd, own, grp ) ) == -1 )
			my_err( "fchown",__LINE__ );
		else
			printf( "Change successful.\n" );
	}
	return 0;
}
