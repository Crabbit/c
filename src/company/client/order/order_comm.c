/*
 *Copyright (c) Xiyou_linux
 *All rights reserver.
 *
 *File		:	order_comm.c
 *Time		:	2012.12.2
 *Editor	:	lili
 *Email		:	lili00681@gmail.com
 *Thanks  to	:	google && openssl
 *
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXSIZE 1024

#define PORT 1124

void my_err( const char * err_string, int line )
{
	fprintf( stderr, "line : %d .",line );
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

		line = X509_NAME_oneline( X509_get_issuer_name( cert ), 0, 0 );
		printf( "Issuer	: %s\n",line );
	}
	else
		printf( "Error!\nDoesn't find CA's information\n" );
}

SSL_CTX *COMM_SSL_INIT( SSL_CTX *ctx )
{
	SSL_library_init();

	OpenSSL_add_all_algorithms();

	SSL_load_error_strings();

	ctx = SSL_CTX_new( SSLv23_client_method() );

	if( ctx == NULL )
		my_err( "SSL_CTX_new",__LINE__ );

	return ctx;
}

int COMM_MAKE__CONNECT( char **argv )
{

	int			socket_fd;

	struct sockaddr_in	server;

	struct hostent		*he;

	if( ( socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
		my_err( "Socket",__LINE__ );

	bzero( &server, sizeof( server ) );

	if( ( he = gethostbyname ( argv[ 1 ] )) == NULL )
		my_err( "Get name",__LINE__ );

	server.sin_family = AF_INET;
	server.sin_port = htons( atoi( argv[ 2 ] ) );
	server.sin_addr = *( ( struct in_addr * )he->h_addr );
	
	if( connect( socket_fd, ( struct sockaddr * )&server, sizeof( server ) ) != 0 )
		my_err( "Connect",__LINE__ );
	printf( "Server %s connected successful!\n",argv[ 1 ] );

	return ( socket_fd );

}

//send information bysl
int SSL_PROCESS_SEND( SSL *ssl )
{
        int                             client_len;

        char                            send_buf[ MAXSIZE + 1 ];

        bzero( send_buf,MAXSIZE + 1 );

        if( fgets( send_buf, MAXSIZE, stdin ) == NULL)
                my_err( "Input",__LINE__ );

        client_len = SSL_write( ssl, send_buf, strlen( send_buf ) );

        if( client_len <= 0 )
        {
                printf( "Send : %s error ! Error code : %d, Error Info : %s.\n ",send_buf, errno, strerror( errno ) );
                return -1;
        }

        else
        {
                printf( "Send : %s  Successfule ! Altogether send %d bytes.\n",send_buf, client_len );
			if( strcmp( send_buf,"QUIT__\n" ) == 0 )
				return 4;
                return 0;
        }
}

//receive information by ssl
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
		printf( "Recieve information : %s\n",recv_buf );
                return 0;
        }
}

int COMM_SSL_PROCESS( int connected_fd, SSL_CTX *ctx )
{
	SSL			*ssl;

	fd_set			rset;

	int			retval;
	int			maxfd = -1;

//if send_state == -1	means	error;
//if send_satae == 0	means	send successful;
//if send_state == 4	means	quit;
	int			send_state;

	ssl = SSL_new( ctx );

	SSL_set_fd( ssl, connected_fd );

	if( SSL_connect( ssl ) == -1 )
		my_err( "SSL_connect",__LINE__ );
	else
	{
		printf( "Connected with %s encryption\n",SSL_get_cipher( ssl ) );
		ShowCerts( ssl );
	}

	printf( "If you want to be disconnected, please input \"QUIT__\" .\n" );

	FD_ZERO( &rset );
	while( 1 )
	{
		FD_SET( fileno( stdin ) , &rset );
		FD_SET( connected_fd, &rset );

		if( fileno( stdin ) > maxfd )
			maxfd = fileno( stdin );
		if( connected_fd > maxfd )
			maxfd = connected_fd;

		maxfd = maxfd + 1;

		printf( "If you wanto to send messages.\nplease input the word you want to transport:\n" );

		retval = select( maxfd, &rset, NULL, NULL, NULL );

		if( retval == -1 )
		{
			printf( "Select Error!\n" );
			break;
		}

		if( FD_ISSET( fileno( stdin ), &rset ) )
		{
			send_state = SSL_PROCESS_SEND( ssl );

			if( send_state == -1 )
				my_err( "SSL_PROCESS_SEND",__LINE__ );
			if( send_state == 4 )
				break;

		}
		if( FD_ISSET( connected_fd, &rset ) )
		{
			if( SSL_PROCESS_RECV( ssl ) == -1 )
				my_err( "SSL_PROCESS_RECV",__LINE__ );
		}
	}

	SSL_shutdown( ssl );

	SSL_free( ssl );

	close( connected_fd );

	SSL_CTX_free( ctx );

	return 0;

}


int main( int argc, char **argv )
{
	int			connected_fd;

	SSL_CTX			*ctx = NULL;


	if( argc != 3 )
	{
		printf( "Usage : < IP Address > < Port >\n" );
		printf( "Example :./program 192.168.200.254 1124\n" );
		exit( 0 );
	}

	ctx = COMM_SSL_INIT( ctx );

	connected_fd = COMM_MAKE__CONNECT( argv );

	COMM_SSL_PROCESS( connected_fd, ctx );

	return 0;

}
