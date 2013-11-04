#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 9999

#define MAXDATASIZE 100

void process( FILE *fp,int sockfd );

char * getMessage ( char * sendline, int len, FILE * fp );

void my_err( const char *err_string,int line )
{
	fprintf( stderr, "line:%d",line );
	perror( err_string );
	exit (1);
}

int main( int argc, char **argv )
{
	int sockfd;
	struct hostent *he;
	struct sockaddr_in server;

	if( argc != 2 )
	{
		printf("Usage: %s <IP address>\n",argv[1]);
		exit(1);
	}
	
	if( ( he = gethostbyname ( argv[ 1 ] ) ) == NULL )
		my_err( "Gethostbyname",__LINE__ );

	if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
		my_err( "Socket",__LINE__ );

	bzero( &server,sizeof( server ) );
	
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr = *( ( struct in_addr *)he->h_addr);
	
	if( connect( sockfd, ( struct sockaddr * )&server, sizeof( server ) ) == -1 )
		my_err( "connect",__LINE__ );

	process( stdin,sockfd );
	close( sockfd );
	return 0;
}


void process( FILE *fp,int sockfd )
{
	char sendline[MAXDATASIZE],recvline[MAXDATASIZE];
	int num;

	printf( "Connected to server.\n" );
	printf( "Input Client's name :" );
	
	if( fgets( sendline, MAXDATASIZE, fp ) == NULL )
	{
		my_err( "Input",__LINE__ );
		return ;
	}

	send( sockfd, sendline,strlen( sendline ),0 );

	while(getMessage( sendline, MAXDATASIZE, fp ) !=NULL )
	{
		send( sockfd, sendline ,strlen( sendline ),0 );
		if( ( num = recv( sockfd, recvline, MAXDATASIZE,0 ) ) == 0 )
		{
			printf( "Server terminated.\n" );
			return ;
		}
		recvline[num]='\0';
		printf("Server Message : %s\n",recvline);
	}
	printf( "\nExit.\n" );
}

char * getMessage ( char * sendline,int len, FILE *fp )
{
	printf( "Input string to server:" );
	return ( fgets(sendline, MAXDATASIZE, fp) );
}
