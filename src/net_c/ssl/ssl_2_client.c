/*
 * Copyright (c) Xiyou_linux
 * All rights reserved.
 *
 * File         :       ssl_1_client.c
 * Time         :       2012.11.27
 * Editir       :       lili
 * Email        :       lili00681@gmail.com
 * Thanks  to   :       google && baidu && google translate ...
 *
 * This sofeware is use for ssl+socket communicate
 * Just for study ^ _ ^
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<resolv.h>
#include<sys/types.h>
#include<unistd.h>
#include<netdb.h>

#include<openssl/ssl.h>
#include<openssl/err.h>

#define MAXSIZE 1024

#define PORT 1126

void my_err( const char * err_string, int line )
{
	fprintf( stderr, "line : %d ",line );
	perror( err_string );
	exit( 1 );
}

void ShowCerts( SSL *ssl )
{
	X509			*cert;
	char			*line;

	cert = SSL_get_peer_certificate( ssl );

	if( cert != NULL )
	{
		printf( "The CA information:\n" );
		line = X509_NAME_oneline( X509_get_subject_name( cert ), 0, 0 );
		printf( "CA	: %s\n",line );
		free( line );

		line = X509_NAME_oneline( X509_get_issuer_name( cert ),0, 0 );
		printf( "Issuer	: %s\n",line );
		free( line );

		X509_free( cert );
	}
	else
		printf( "ERROR!\nDoesn't find CA's information\n" );
}

int main( int argc, char **argv )
{
	int			socket_fd;
	int			len;

	struct sockaddr_in	server;
	struct hostent		*he;

	char			recv_buf[ MAXSIZE + 1 ],send_buf[ MAXSIZE + 1 ];

	SSL_CTX			*ctx;
	SSL			*ssl;

	if( argc != 3 )
	{
		printf( "Usage : < IP Address > <Port>\nExamle : ./program 193.168.200.254 1126\n" );
		exit( 0 );
	}

//SSL lib initalization
	SSL_library_init();

//Loading SSL algorithms
	OpenSSL_add_all_algorithms();

//loading SSL error information
	SSL_load_error_strings();

	ctx = SSL_CTX_new( SSLv23_client_method() );

	if( ctx == NULL )
		my_err( "SSL_CTX_new",__LINE__ );

	if( (  socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) )< 0 )
		my_err( "Socket",__LINE__ );

	bzero( &server, sizeof( server ) );

	if( ( he = gethostbyname ( argv[ 1 ] ) ) == NULL )
		my_err( "Socket",__LINE__ );


	server.sin_family = AF_INET;
	server.sin_port = htons( atoi( argv[ 2 ] ) );
	server.sin_addr = *( ( struct in_addr * )he->h_addr );

//	if( inet_aton( argv[ 1 ],( struct in_addr * )&server.sin_addr.s_addr ) == 0 )
//		my_err( "IP Address ERROR.",__LINE__ );

		
	if( connect( socket_fd, ( struct sockaddr * )&server, sizeof( server ) ) != 0 )
		my_err( "Connect",__LINE__ );

	printf( "Server %s connected.\n", argv[ 1 ] );

//produce a new ssl basic ctx
	ssl = SSL_new( ctx );
	SSL_set_fd( ssl,socket_fd );

//build a ssl connect
	if( SSL_connect( ssl ) == -1 )
		my_err( "SSL_connect",__LINE__ );
	else
	{
		printf( "COnnected with %s encryption\n",SSL_get_cipher( ssl ) );
		ShowCerts( ssl );
	}

//receive server information,the most can receive MAXSIZE bytes
	bzero( recv_buf,MAXSIZE + 1 );

	len = SSL_read( ssl, recv_buf, MAXSIZE );

	if( len <= 0 )
	{
		printf( "Information receive failed! Error code : %d , Error information : %s",errno, strerror( errno ) );
		goto finish;
	}
	else
		printf( "Information receive successful.\nInformation : %s.\nAlmost receive %d bytes\n",recv_buf, len );

	bzero( send_buf, MAXSIZE + 1 );

	strcpy( send_buf,"From client ----> server" );

	len = SSL_write( ssl, send_buf, strlen( send_buf ) );

	if( len < 0 )
		printf( "Information %s send failed. Error code : %d , Error information %s \n.",send_buf, errno, strerror( errno ) );
	else
		printf( "Information %s send successful. Almost send %d bytes.\n",send_buf, len );

	finish :
		SSL_shutdown( ssl);
		SSL_free( ssl );
		close( socket_fd );
		SSL_CTX_free( ctx );

	return 0;
}
