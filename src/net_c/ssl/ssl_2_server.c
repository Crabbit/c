/*
 * Copyright (c) Xiyou_linux
 * All rights reserved.
 *
 * File 	:	ssl_2_server.c
 * Time 	:	2012.11.28
 * Editor	:	lili
 * Email	:	lili00681@gmail.com
 * Thanks  to	:	google && baidu && google translate ...
 *
 * Change log
 * 	the first	:	increase the communicate function
 * 	the second	:	server can accept lots of request by fora process
 * 	the third	:	the code split the different function
 *
 * This sofeware is use for ssl+socket communicate
 * Just for study ^ _ ^
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<resolv.h>

#include<openssl/bio.h>
#include<openssl/err.h>
#include<openssl/ssl.h>
#include<dlfcn.h>

#define MAXSIZE 1024
#define BACKLOG 32

#define PORT 1126

#define PKEY_FILE "ssl_server_key.pem"
#define CERT_FILE "ssl_server_cert.pem"

int SSL_PROCESS( int connect_fd,struct sockaddr_in client, SSL_CTX *ctx);
int SSL_PROCESS_SEND( SSL *ssl );
int SSL_PROCESS_RECV( SSL *ssl );

void my_err( const char *err_string, int line )
{
	fprintf( stderr,"line : %d  ",line );
	perror( err_string );
	exit( 1 );
}


int main( int argc, char **argv )
{
	int				socket_fd,connect_fd;
	socklen_t			client_len;

	struct sockaddr_in		server;
	struct sockaddr_in		client;


	SSL_CTX				*ctx;

	pid_t				pid;

//initalization SSL lib
	SSL_library_init();

//loading SSL algorithms
	OpenSSL_add_all_algorithms();

//loading all SSL error information
	SSL_load_error_strings();

//use SSL V2 and V3 to produce a SSL_CTX-----SSL Content text
//You also can use V2----SSLv2_server_method(),or V3-----SSLv3_server_method()
//	if ( ( ctx = SSL_CTX_new( SSLv23_server_method() ) ) == NULL );
	ctx = SSL_CTX_new( SSLv23_server_method() );
	if ( ctx == NULL )
		my_err( "SSL_CTX_new",__LINE__ );

//loading user CA
	if( SSL_CTX_use_certificate_file( ctx, CERT_FILE, SSL_FILETYPE_PEM ) <= 0  )
		my_err( "SSL_CTX_use_certficate_file",__LINE__ );

//loading user key
	if( SSL_CTX_use_PrivateKey_file( ctx, PKEY_FILE, SSL_FILETYPE_PEM ) <= 0 )
		my_err( "SSL_CTX_use_PrivateKey_file",__LINE__ );

//check user key
	if( !SSL_CTX_check_private_key( ctx ) )
		my_err( "SSL_CTX_check_private_key",__LINE__ );

//make a socket
	if( ( socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
		my_err( "Socket",__LINE__ );

//reuse address
	int opt = SO_REUSEADDR;
	if( setsockopt( socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( &opt ) ) < 0  )
		my_err( "setsockopt",__LINE__ );

//initalization socket
	bzero( &server, sizeof( server ) );

	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr.s_addr = htonl( INADDR_ANY );

//bind socket,address,port
	if( bind( socket_fd,( struct sockaddr  *)&server, sizeof( server ) ) == -1 )
		my_err( "Bind",__LINE__ );

//socket : close ---> lisen
	if( listen( socket_fd,BACKLOG ) == -1 )
		my_err( "listen",__LINE__ );

	client_len = sizeof( struct sockaddr );


	while ( 1 )
	{

		if( ( connect_fd = accept( socket_fd, ( struct sockaddr * )&client, &client_len ) ) == -1 )
			my_err( "Accept",__LINE__ );

//father
		if( ( pid = fork() ) > 0 )
		{
			close( connect_fd );
			continue;
		}

//son
		else
			if( pid == 0 )
			{
				close( socket_fd );
				if( SSL_PROCESS( connect_fd, client, ctx ) == -1) ;
					break;
				continue;
			}
			else
				my_err( "fork",__LINE__ );

	}

//shutdown listen socket
	close ( socket_fd );

	return 0;
}


// socket ----> SSL socket
int SSL_PROCESS( int connect_fd,struct sockaddr_in client, SSL_CTX *ctx)
{
	SSL	 			*ssl;

		printf( "Server : Got a connection from %s, port %d, socket %d\n",inet_ntoa( client.sin_addr ),ntohs( client.sin_port ), connect_fd );

//generate a new SSL based ctx
		ssl = SSL_new( ctx );
//add the connected socket to SSL
		SSL_set_fd( ssl,connect_fd );

//buile a SSL connect
		if( SSL_accept( ssl ) == -1 )
		{
			perror( "Accept" );
			close( connect_fd );
			return -1;
		}

//start handle the information of every connect
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


//include function	:
// |-- Send message	:  SSL_PROCESS_SEND
// |-- receive message	:  SSL_PROCESS_RECV

//send information
int SSL_PROCESS_SEND( SSL *ssl )
{
	int 				client_len;

	char				send_buf[ MAXSIZE + 1 ];

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

//recieve information
int SSL_PROCESS_RECV( SSL *ssl )
{
	int 				client_len;

	char				recv_buf[ MAXSIZE + 1 ];
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
