#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>			//netdb.h is needed for struct hostent and the funcation--gethostbyname
#include<unistd.h>

#define PORT	9999

#define MAXDATASIZE 100


void my_err( const char * err_string, int line )
{
	fprintf( stderr, "line:%d " , line );
	perror( err_string );
	exit(1);
}


int main(int argc,char **argv)
{
	int sockfd,num;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in server;

	if(argc != 2)
	{
		printf("Usage: %s <IP address>\n",argv[1]);
		exit(1);
	}
	
	if ( he = gethostbyname(argv[1]) == NULL )
		my_err("gethostbyname",__LINE__);
// funcation--gethostbyname return a struct hostent;
	
	if( sockfd == socket( AF_INET, SOCK_STREAM, 0 ) == -1 )
		my_err( "sock",__LINE__ );
	
	bzero( &server,sizeof(server) );
		
		server.sin_family = AF_INET;
		server.sin_port = htons( PORT );
		server.sin_addr = *( ( struct in_addr * )he->h_addr  );

	if( connect( sockfd,(struct sockaddr *)&server ,sizeof( server ) ) == -1 )
		my_err( "connect",__LINE__ );
	
	if( ( num = recv( sockfd, buf, MAXDATASIZE, 0 )) == -1 )
		my_err( "recv",__LINE__ );
	
	buf[num-1] = '\0';
	printf( " server message: %s ",buf );
	close(sockfd);
	return 0;
}
