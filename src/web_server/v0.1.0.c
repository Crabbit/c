/*-----------------------------------------------------------------------------------
  This software is copyright in 2012.10.10 by Lili.
  The version is 0.1.0
  The software is like with Apache or nginx,it's a Web Server.
  										Thanks~
  -----------------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>

//listen port is 80
#define PORT 80

//kernel manager listened queue(dui lie)
//queue = incomlpete connection queue + completed connection queue
#define BACKLOG 32

//recieve and send length
#define MAXDATASIZE 1024

void Process_Client( int connect_fd, struct sockaddr_in client );
int Make_Listen_Socket( void );
void Open_Html( char Read_Buf[] , char path[]);

void my_err( const char * err_string,int line )
{
	fprintf( stderr,"line","%d",line );
	perror( err_string );
	exit( 1 );
}

int main()
{
	int 			sock_fd,connect_fd;
	int			client_len;
	struct sockaddr_in 	client;
	pid_t 			pid;
	
	sock_fd = Make_Listen_Socket();

	client_len = sizeof( client );	

	while( 1 )
	{
		if( ( connect_fd = accept( sock_fd, ( struct sockaddr * )&client ,&client_len  ) ) == -1 )
			my_err( "Accept",__LINE__ );

//print some information
		printf( "\nAccept a new client.\n\t\tIP : %s\n",inet_ntoa( client.sin_addr ) );

//father and the son region
		if( ( pid = fork() ) > 0 )
		{
			close( connect_fd );
			continue;
		}
		else
			if( pid == 0 )
			{
				close( sock_fd );
				Process_Client( connect_fd, client );
			}

	}
	return 0;
}

int Make_Listen_Socket( void )
{
	int 			sock_fd;

	struct sockaddr_in	server;

//Make socket
	if( ( sock_fd = socket( AF_INET, SOCK_STREAM, 0  ) ) == -1 )
		my_err( "Socket",__LINE__ );

//reuse address
	int opt = SO_REUSEADDR;
	if( setsockopt( sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 )
		my_err( "Setsock Opt",__LINE__ );

//initalization socket
	bzero( &server,sizeof( server ) );

	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr.s_addr = htonl( INADDR_ANY );

//bind socket, address, port
	if( bind( sock_fd,( struct sockaddr*  )&server, sizeof( server ) ) == -1)
		my_err( "Bind",__LINE__ );

//socket : Closed --> listen
	if( listen( sock_fd, BACKLOG ) == -1 )
		my_err( "Listen",__LINE__ );

	return sock_fd;
}

void Process_Client( int connect_fd, struct sockaddr_in client )
{
	int			ret = 0;
	char			recv_buf[ MAXDATASIZE ],send_buf[MAXDATASIZE];
	char			Read_Buf[65535];

//receive the information of the clients request
	if( ( ret = recv( connect_fd,recv_buf, MAXDATASIZE, 0 ) ) < 0 )
		my_err( "Receive",__LINE__ );

	recv_buf[ ret - 1 ] = '\0';

	int			i = 0,j = 0;
	char			path[128];

	strcpy( path,"/var/www/html" );

	j = strlen( "/var/www/html" );

	for( i = 4; recv_buf[ i ] != ' ' ; i++,j++ ) 
		path[ j ] = recv_buf[ i ];

	Open_Html( Read_Buf,path );

	send( connect_fd, Read_Buf, strlen( Read_Buf ),0 );

//	printf( "\n%s\n",recv_buf );
//	printf( "######################\n%s\n#######################",Read_Buf );

}

void Open_Html( char Read_Buf[] , char path[])
{
	int 			FileD;
	int			ret,len;

	if( path[ strlen( path ) - 1 ] == '/')
		strcat( path,"index.html\0" );

//	printf( "\n\n-------%s-------\n",path );
	if( ( FileD = open( path,O_RDONLY ) ) == -1 )
			my_err( "Open File",__LINE__ );
//get the length of the index.html,and keep the point is in the start
	if( lseek( FileD, 0, SEEK_END ) == -1 )
		my_err( "Lseek",__LINE__ );

	if( ( len = lseek( FileD, 0, SEEK_CUR ) ) == -1 )
		my_err( "Lseek",__LINE__ );

	if( ( lseek( FileD, 0, SEEK_SET ) ) == -1 )
		my_err( "Lseek",__LINE__ );

	if( ( ret = read( FileD, Read_Buf, len ) ) < 0 )	
		my_err( "Read",__LINE__ );

	close( FileD );
}
