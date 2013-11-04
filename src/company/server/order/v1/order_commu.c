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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <resolv.h>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <dlfcn.h>

#define PORT 1124

#define BACKLOG 32

#define MAXSIZE 1024

#define PKEY_FILE "ssl_server_key.pem"
#define CERT_FILE "ssl_server_cert.pem"

//handle error
void my_err( const char *err_string,int line )
{
	fprintf( stderr,"line : %d",line );
	perror( err_string );
	exit( 1 );
}


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
int COMMUNICATE_SOCKET_MAKE__LISTEN( char IP_ADDRESS[] )
{
	int 				socket_fd;

	struct	sockaddr_in		server;
	struct	hostent			*he;

//make socket
	if( ( socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
		my_err( "Socket",__LINE__ );

//reuse address
	int opt = SO_REUSEADDR;
	if( setsockopt( socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 )
		my_err( "Socket reuse address",__LINE__ );

//initalization socket
	bzero( &server, sizeof( server ) );

	if( ( he = gethostbyname( IP_ADDRESS ) ) == NULL )
		my_err( "Get Host by name",__LINE__ );

	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr = *( ( struct in_addr * )he->h_addr );

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

        bzero( send_buf,MAXSIZE + 1 );

        printf( "Server -------> Client\n" );
        printf( "Pleae input the messages :" );

        if( fgets( send_buf, MAXSIZE, stdin ) == NULL);
                my_err( "Input",__LINE__ );

        client_len = SSL_write( ssl, send_buf, strlen( send_buf ) );
                
        if( client_len <= 0 )
        {       
                printf( "Send (-- %s --) error ! Error code : %d, Error Info : %s.\n ",send_buf, errno, strerror( errno ) );                                           
                return -1;                                                         
        }

        else
        {
                printf( "Send (-- %s --) Successfule ! Altogether send %d bytes.\n",send_buf, client_len );
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
                printf( "Recieve information successful! Altogether recieve %d bytes.\n", client_len );
                return 0;
        }
}


//SSL process
int COMM_SSL_PROCESS( int connect_fd, struct sockaddr_in client, SSL_CTX *ctx )
{
	SSL				*ssl;
		printf( "Server : Got a connection from %s, port %d, socket %d\n",inet_ntoa( client.sin_addr ), ntohs( client.sin_port ), connect_fd );

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

//start handle the infromation of every connect
	if( SSL_PROCESS_SEND( ssl ) == -1 )
		my_err( "SSL_PROCESS_SEND",__LINE__ );

	if( SSL_PROCESS_RECV( ssl ) == -1 )
		my_err( "SSL_PROCESS_RECV",__LINE__ );

//shutdown SSL connect
	SSL_shutdown( ssl );

//Release
	SSL_free( ssl );

//shutdown socket
	close( connect_fd );

//Release CTX
	SSL_CTX_free( ctx );

	return 0;

}


//int COMMUNICATE_MAIN( char IP_ADDRESS[] )
int main()
{
	char				IP_ADDRESS[16];
	int				COMM_socket_fd,COMM_connect_fd;

	pid_t				pid;
	struct sockaddr_in		client;
	socklen_t			client_len;

	SSL_CTX				*ctx = NULL;

	ctx = COMMUNICATE_SSL_INIT( ctx );

	COMM_socket_fd = COMMUNICATE_SOCKET_MAKE__LISTEN( IP_ADDRESS );

	client_len = sizeof( struct sockaddr );

	while( 1 )
	{
		if( ( COMM_connect_fd = accept( COMM_socket_fd, ( struct sockaddr * )&client, &client_len ) ) == -1 )
			my_err( "Connect",__LINE__ );

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
				close( COMM_socket_fd );
				if( COMM_SSL_PROCESS( COMM_connect_fd, client, ctx ) == -1 );
					break;
				continue;
			}
			else
				my_err( "Fork",__LINE__ );
	}

//shutdown listen socket
	close( COMM_socket_fd );

	return 0;
}
