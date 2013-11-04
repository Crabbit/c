#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
int main()
{
	int file;
	char *a;

	char *read_buf;

	char i;
	file = open( "COMM_FILE_ONLINE",O_APPEND | O_RDWR );
	a = "222.24.8.8";

	write( file, "8.8.8.8", 7 );
	i = 15 - strlen( "8.8.8.8" );
	printf( "%d\n",i );
	for( ; i != 0; i--)
		write( file, " ",1 );
	write( file, " CONNECTING\n", 12 );


	write( file, a, strlen(a) );
	i = 15 - strlen(a);
	printf( "%d\n",i );
	for( ; i != 0; i-- )
		write( file, " ",1 );
	write( file, " CONNECTING\n", 12 );

	close( file );
	
	printf( "The file :\n" );
	file = open( "COMM_FILE_ONLINE", O_RDWR );
	read( file, read_buf, 16 );
	printf( "%s",read_buf );

	write( file, "8.8.8.8", 7 );
	close( file );

	file = open( "COMM_FILE_ONLINE", O_RDONLY );

	read( file, read_buf, 23);
	printf( "%s",read_buf );

/*	read( file, read_buf, 16 );
	printf( "%s",read_buf );
	read( file, read_buf, 11 );
	printf( "%s",read_buf );
*/
	return 0;
}
