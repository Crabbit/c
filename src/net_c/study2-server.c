#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 1126

#define BACKLOG 10

#define MAXDATASIZE 100

void process_cli( int connectfd, struct sockaddr_in client );

void my_err( const char * err_string, int line )
{
	fprintf( stderr, "line : %d",line );
	perror( err_string );
	exit(1);
}

main()
{
	int sockfd, connectfd;
	pid_t pid;						
	struct sockaddr_in server;
	struct sockaddr_in client;
	
	int len;

	if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
	{
		my_err("socket",__LINE__);
	}

//地址重用选项	
	int opt = SO_REUSEADDR;
	setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) );

	bzero(&server,sizeof( server ));
	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr.s_addr = htonl( INADDR_ANY );		//Attention,---INADDR_ANY---any addres,the value is 0;

	if( bind( sockfd, ( struct sockaddr * )&server,sizeof( server ) ) == -1 )
		my_err( "bind",__LINE__ );
	
	if( listen(sockfd,BACKLOG) == -1 )
		my_err("listen",__LINE__);
	
	len = sizeof( client );
	
	while( 1 )
	{
		if( ( connectfd = accept( sockfd, (struct sockaddr *)&client, &len ) ) == -1)
			my_err( "accept",__LINE__ );
		
//father 
		if( ( pid =fork() ) > 0 )
		{
			close( connectfd );
			continue;
		}

//son
		else 
			if( pid ==0 )
			{
				close( sockfd );
				process_cli( connectfd,client );
				continue;
			}
		
		else 
				my_err( "fork",__LINE__ );
	}
	
	close ( sockfd );
	return 0;
}
void process_cli( int connectfd,struct sockaddr_in client )
{
	int num;
	char recvbuf[ MAXDATASIZE ], sendbuf[ MAXDATASIZE ], cli_name[ MAXDATASIZE ];
	printf( "You got a connection from %s .",inet_ntoa(client.sin_addr) ) ;
	num = recv( connectfd,cli_name,MAXDATASIZE,0 );

//recive the bytes is 0----means recive nothing
	if( num == 0 )
	{
		close ( connectfd );
		printf( "Clients are disconnected.\n" );
		return;
	}

	cli_name[num-1] = '\0';
	
	printf( "Clients name is %s .\n",cli_name );

	while( num = recv( connectfd, recvbuf, MAXDATASIZE, 0 ) )
	{
		recvbuf[num-1] = '\0';
		printf( "Recived client ( %s ) message : %s\n", cli_name, recvbuf );
		int i = 0;

//K=3 sercert
		for( i = 0; i < num-1; i++ )
		{
			if( ( recvbuf[i] >= 'a' && recvbuf[i] < 'z' ) || ( recvbuf[i] >= 'A' && recvbuf[i] < 'Z') )	
			{
				recvbuf[i] = recvbuf[i] + 3;
				if( (  recvbuf[i] > 'Z' && recvbuf[i] < 'Z'+3) || (recvbuf[i] > 'Z') )
					recvbuf[i] = recvbuf[i] - 26;			//if the word more than z,return to  a
			}
			sendbuf[i] = recvbuf[i];
		}
		sendbuf[num-1] = '\0';
		send( connectfd, sendbuf, strlen( sendbuf ), 0 );
	}
	close( connectfd );
}
