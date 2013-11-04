#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define PORT 9999

#define BACKLOG 10

//error funcation
void my_err( const char * err_string, int line )
{
	fprintf( stderr, "line:%d " , line );
	perror( err_string );
	exit(1);
}

//main funcation
int main( int argc , char **argv )
{

	int	 sockfd,connectfd;

// defined  two socket

	struct sockaddr_in	 server;
	struct sockaddr_in 	client;

//socklen_t == unsigned short
	socklen_t 	addrlen;

	

	bzero( &server , sizeof( server ) );
		server.sin_family = AF_INET;					//ipv4
		server.sin_port = htons ( PORT );				//port
//		server.sin_addr.s_addr = inet_addr ( "argv[1]" );		//IP address
	
	addrlen = sizeof( server );
// create a TCP socket	AF_INET----ipv4 , SOCK_STREAM------tcp , prototocol=0
	if( ( sockfd = socket( AF_INET , SOCK_STREAM , 0 )) == -1)
		my_err("socket",__LINE__);

//地址重用选项，当程序结束后，释放端口，让其他程序可以利用此端偶
	int opt = SO_REUSEADDR;							//opt用来存放获得的套接字选项
	setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt) );	//SOL_SOCKET——通用套接字（套接字级别），SO_REUSEADDR——解除绑定问题

//bind the address and the port
	if( bind( sockfd , (struct sockaddr *)&server , sizeof(server) ) == -1 )
		my_err("bind",__LINE__);
	
// Active initiative sockets to  passive socket      server: CLOSED -> LITEN
	if( listen( sockfd , BACKLOG ) == -1 )	
		my_err("listen",__LINE__);
// listen return 0
// --listen make sockedfd -> listenfd  ,  the sockedfd's status is listened

// return a socketfd (connectfd) 
	if( (connectfd = accept( sockfd , (struct sockaddr *)&server , &addrlen )) == -1 )
		my_err("listen",__LINE__);

//printf the clients IP and the port
	printf( "you got a connection from client's ip is %s,port is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port) );
	
//send the information to client
//	char shu[100];
//	int i=0;
//	while( i != 5 )
//	{
//		printf("Please input the information:");
//		scanf("%s",shu);
		send(connectfd,"12345123451234512345\n1234512345\n",50,0 );
//		i++;
//	}
//	if( connect( connectfd , (struct sockaddr * )&server , sizeof(server) ) == -1 )
//		my_err("connect",__LINE__);
	
	close( connectfd );
	close( sockfd );
	return 0;
}
