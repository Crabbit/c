/*
 * Copyright (c) Xiyou_linux
 * All rights reserved.
 *
 *File			:	order_commu.c
 *Time			:	2012.11.24
 *Editor		:	Lili		
 *Email			:	lili00681@gmail.com
 *Thanks		:	google && ssl ...
 *
 *
 * This part is for communication.
 * Use the socket with ssl.
 * Attention		:	This version is synchronous communication
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <resolv.h>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <dlfcn.h>

#include "order_file.h"
#include "order_errno.h"

#define PORT 1124

#define BACKLOG 32

#define MAXSIZE 1024

#define PKEY_FILE "ssl_server_key.pem"
#define CERT_FILE "ssl_server_cert.pem"

#define DISCONNECT 0
#define CONNECTING 1



//SSL initalization
SSL_CTX *COMMUNICATE_SSL_INIT( SSL_CTX *ctx )
{

//initalization SSL lib
	SSL_library_init();

//loading SSL algorithms
	OpenSSL_add_all_algorithms();

//loading all SSL err information
	SSL_load_error_strings();

//use SSL V2 and V3 to produce a SSL_CTX------SSL content text
	ctx = SSL_CTX_new( SSLv23_server_method() );
	if ( ctx == NULL )
		my_err( "SSL_CTX_new",__LINE__ );

//loading user CA
	if( SSL_CTX_use_certificate_file( ctx, CERT_FILE, SSL_FILETYPE_PEM ) <=0 )
		my_err( "SSL_CTX_use_certificate_file",__LINE__ );

//loading user key
	if( SSL_CTX_use_PrivateKey_file( ctx, PKEY_FILE, SSL_FILETYPE_PEM ) <=0 )
		my_err( "SSL_CTX_use_PrivateKey_file",__LINE__ );

//check user key
	if( !SSL_CTX_check_private_key( ctx ) )
		my_err( "SSL_CTX_check_private_key",__LINE__ );

	return ctx;

}

//make socket 
int COMMUNICATE_SOCKET_MAKE__LISTEN( void )
{
	int 				socket_fd;

	struct	sockaddr_in		server;

//make socket
	if( ( socket_fd = socket( AF_INET, SOCK_STREAM, 0 )) == -1 )
		my_err( "Socket",__LINE__ );

//reuse address
	int opt = SO_REUSEADDR;
	if( setsockopt( socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 )
		my_err( "Socket reuse address",__LINE__ );

//initalization socket
	bzero( &server, sizeof( server ) );

	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr.s_addr = htonl( INADDR_ANY );

//bind socket,address,port
	if( bind( socket_fd, (struct sockaddr *)&server, sizeof( server ) ) == -1 )
		my_err( "Bind",__LINE__ );

//socket : closed --> listen
	if( listen( socket_fd, BACKLOG ) == -1 )
		my_err( "Listen",__LINE__ );

	return socket_fd;
}

//send information by SSL connect
int SSL_PROCESS_SEND( SSL *ssl )
{
        int                             client_len;

        char                            send_buf[ MAXSIZE + 1 ];
	char				PRESS;

        bzero( send_buf,MAXSIZE + 1 );

	scanf( "%c",&PRESS );
	if( PRESS == '#' )
	{
		printf( "\n" );
		printf( "This is ip-address of the onlined:\n" );
	}

	printf( "OK. Now,you can send the messages, Please input :" );

        if( fgets( send_buf, MAXSIZE, stdin ) == NULL)
                my_err( "Input",__LINE__ );

        client_len = SSL_write( ssl, send_buf, strlen( send_buf ) );
                
        if( client_len <= 0 )
        {       
                printf( "Send :  %s  error ! Error code : %d, Error Info : %s.\n ",send_buf, errno, strerror( errno ) );                                           
                return -1;                                                         
        }

        else
        {
                printf( "Send :  %s  Successfule ! Altogether send %d bytes.\n",send_buf, client_len );
                return 0;
        }
}

//recieve information by SSL connect
int SSL_PROCESS_RECV( SSL *ssl )
{
        int                             client_len;

        char                            recv_buf[ MAXSIZE + 1 ];


        bzero( recv_buf, MAXSIZE + 1 );

        client_len = SSL_read( ssl,recv_buf, MAXSIZE );

        if( client_len <= 0 )
        {
                printf( "Recieve information failed ! Error code : %d, Error info : %s\n.",errno, strerror( errno ) );
                return -1;
        }
        else
        {
		if( strcmp( recv_buf , "QUIT__\n" ) == 0 )
			return 4;
		else
			{
        		        printf( "Recieve information successful! Altogether recieve %d bytes.\n", client_len );
				printf( "Recieve information : %s\n",recv_buf );
        		        return 0;
			}
        }
}


//SSL process
int COMM_SSL_PROCESS( int connect_fd, struct sockaddr_in client, SSL_CTX *ctx )
{
	SSL				*ssl;

	fd_set				rset;
//	struct timeval 			timev;
	int 				retval;
	int				maxfd = -1;
	
//if recv_state == -1	means error;
//if recv_state == 0	means recieve successful;
//if recv_state == 4	means quit;
	int				recv_state;

	char *				IP_ADDRESS;

//change the state, must save the ip.
	IP_ADDRESS = inet_ntoa( client.sin_addr );
//save the ip address that connecting 
	if( COMM_SAVE_IPADDRESS( inet_ntoa( client.sin_addr ) ) == -1 )
		my_err( "Save IPaddress",__LINE__ );

	printf( "New connection : Got a new connection from %s, port %d, socket %d\n",inet_ntoa( client.sin_addr ), ntohs( client.sin_port ), connect_fd );

//generate a new SSL based ctx
	ssl = SSL_new( ctx );

//add the connected socket to SSL
	SSL_set_fd( ssl, connect_fd );

//build a SSL connect
	if( SSL_accept( ssl ) == -1 )
	{
		perror( "Accept" );
		close( connect_fd );
		return -1;
	}

	FD_ZERO( &rset );
	while( 1 )
	{
		FD_SET( fileno( stdin ) , &rset);
		FD_SET( connect_fd, &rset );

		if( fileno( stdin ) > maxfd )
				maxfd = fileno( stdin );
		if( connect_fd > maxfd )
				maxfd = connect_fd;
		maxfd = maxfd + 1;

                printf( "If you wanto to send messages,please press   #\n" );

		retval = select( maxfd, &rset, NULL, NULL, NULL );

		if( retval == -1 )
		{
			printf( "Select ERROR!\n" );
			break;
		}

//start handle the infromation of every connect
		if( FD_ISSET( fileno( stdin ), &rset ))
		{
			if( SSL_PROCESS_SEND( ssl ) == -1 )
				my_err( "SSL_PROCESS_SEND",__LINE__ );
		}

		if( FD_ISSET( connect_fd, &rset ))
		{
			recv_state =  SSL_PROCESS_RECV( ssl );

			if( recv_state == -1 )
				my_err( "SSL_PROCESS_RECV",__LINE__ );
			if( recv_state == 4 )
				break;
		}
	}

//shutdown SSL connect
	SSL_shutdown( ssl );
	printf( "SSL connect shutdonw\n" );

//Release
	SSL_free( ssl );
	printf( "ssl free\n" );

//shutdown socket
	close( connect_fd );
	printf( "socket shutdown\n" );

//Release CTX
	SSL_CTX_free( ctx );
	printf( "ssl ctx free.\n" );

	if ( COMM_FILE_STATE_EXCHANGE( IP_ADDRESS ) == -1 )
//		my_err( "State exchange.",__LINE__ );
		pr_err( "COMM_FLE_STATE_EXCHANGE",errno, strerror( errno ) );

	return 0;

}


//int COMMUNICATE_MAIN( void )
int main()
{
	int				COMM_socket_fd,COMM_connect_fd;

	pid_t				pid;
	struct sockaddr_in		client;
	socklen_t			client_len;

	SSL_CTX				*ctx = NULL;

	COMM_CREATE_FILE( "COMM_FILE_ONLINE" );

	ctx = COMMUNICATE_SSL_INIT( ctx );

	COMM_socket_fd = COMMUNICATE_SOCKET_MAKE__LISTEN();

	client_len = sizeof( struct sockaddr );

	while( 1 )
	{

		printf( "Start Successful\n" );
		if( ( COMM_connect_fd = accept( COMM_socket_fd, ( struct sockaddr * )&client, &client_len ) ) != -1 )
		{
			printf( "A new client is connecting.\n" );
		}
		else
			my_err( "Connect",__LINE__ );

/*
//father
		if( ( pid = fork() ) > 0 ) 
		{
			close( COMM_connect_fd );
			continue;
		}

//son
		else
			if( pid == 0 )
			{
*/				close( COMM_socket_fd );
				if( COMM_SSL_PROCESS( COMM_connect_fd, client, ctx ) == -1 )
					break;
/*				continue;
			}
			else
				my_err( "Fork",__LINE__ );
*/	}

//shutdown listen socket
	close( COMM_socket_fd );

	return 0;
}
