#ifndef __ORDER_COMMU__
#define __ORDER_COMMU__

//SSL initalization
SSL_CTX *COMMUNICATE_SSL_INIT( SSL_CTX *ctx );

//make socket 
int COMMUNICATE_SOCKET_MAKE__LISTEN( void )

//send information by SSL connect
int SSL_PROCESS_SEND( SSL *ssl )

//recieve information by SSL connect
int SSL_PROCESS_RECV( SSL *ssl )

//SSL process
int COMM_SSL_PROCESS( int connect_fd, struct sockaddr_in client, SSL_CTX *ctx )

//Commnuicate main function
int COMMUNICATE_MAIN( void )

#endif
