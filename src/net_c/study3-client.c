#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 9999

#define MAXDATASIZE 1024

void process( FILE *fp,int sock_fd );


void my_err( const char *err_string, int line )
{
	fprintf( stderr,"line:%d",line );
	perror( err_string );
	exit( 1 );
}


int main( int argc, char **argv )
{
	int sock_fd,
	struct hostent *he;
	struct sockaddr_in server;

	

	if( ( sock_fd = socket( AF_INET, SOCK_STREAM,0 ) ) == -1 )
		my_err( "Socket",__LINE__ );

	bzero( &server,sizeof( server ) );

		server.sin_family = AF_INET;
		server.sin_port = htons( PORT );
		server.sin_addr = *( ( struct in_addr * )he->h_addr );
		
	if( connect( sock_fd,( struct sockaddr * )&server, sizeof( server ) ) == -1 )
		my_err( "Connect",__LINE__ );


}
