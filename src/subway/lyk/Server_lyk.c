#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include"subway.h"


#define PORT 9999

#define BACKLOG	20

#define MAXDATASIZE 3000

void process_client( int connect_fd, struct sockaddr_in client );

void my_err( const char * err_string, int line )
{
	fprintf( stderr,"line : %d",line );
	perror( err_string );
	exit( 1 );
}


int main()
{
	int	 		sock_fd,connect_fd;
	
	pid_t			pid;
	struct sockaddr_in	server,client;
	int			cli_len;

//创建套接子
	if( ( sock_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1)
		my_err( "Socket",__LINE__ );

//地址重用
	int opt = SO_REUSEADDR;
	if( setsockopt( sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 )
		my_err( "Setsockopt",__LINE__ );

//初始化服务器端地址结构
	bzero( &server, sizeof( server ) );

	server.sin_family = AF_INET;
	server.sin_port = htons( PORT );
	server.sin_addr.s_addr = htonl( INADDR_ANY );

//绑定套接字和端口
	if( bind( sock_fd, ( struct sockaddr * )&server, sizeof( server ) ) == -1 )
		my_err( "Bind",__LINE__ );

//将套接子转化为监听套接子
	if( listen( sock_fd, BACKLOG ) == -1 )
		my_err( "Listen",__LINE__ );

	cli_len = sizeof( client );
		
	while( 1 )
	{
		if( ( connect_fd = accept( sock_fd, ( struct sockaddr * )&client, &cli_len ) ) == -1 )
			my_err( "Accept",__LINE__ );

//输出信息，表示已经建立连接
		printf( "\t\tAccept a new client.\n\t\tip : %s\n",inet_ntoa( client.sin_addr ) );

//父进程,关闭这个连接，并等候其他连接
		if( ( pid = fork() ) > 0 )
		{
			close( connect_fd );
			continue;
		}

//子进程，用来处理该连接
		else
			if( pid == 0 )
			{
				close( sock_fd );
				process_client( connect_fd, client );
				continue;
			}
			

	}
	
	close( sock_fd );
	return 0;
}


void process_client( int connect_fd, struct sockaddr_in client )
{
	int ret;
	char recv_buf[ MAXDATASIZE ], send_buf[ MAXDATASIZE ];
	char chooseway[3],start_platform[MAXDATASIZE],end_platform[MAXDATASIZE];
	int chooseWay;
	int status = 0;


/*		if( ( ret = recv( connect_fd,recv_buf, MAXDATASIZE , 0 ) ) < 0 )
		{
			my_err( "Recv",__LINE__ );
			status = -1;
		}
		recv_buf[ret] = '\0';
//		printf( "---------%s----\n",recv_buf );

		strcpy( chooseway, recv_buf );
		chooseWay = atoi(chooseway);
	

		if( ( ret = recv( connect_fd,recv_buf, MAXDATASIZE , 0 ) ) < 0 )
		{
			my_err( "Recv",__LINE__ );
			status = -1;
		}
		recv_buf[ret] = '\0';
//		printf( "=========%s====\n",recv_buf );

		strcpy( start_platform, recv_buf );

		
		if( ( ret = recv( connect_fd,recv_buf, MAXDATASIZE , 0 ) ) < 0 )
		{
			my_err( "Recv",__LINE__ );
			status = -1;
		}
		recv_buf[ret] = '\0';
//		printf( "!!!!!!!!!!!!!!!%s!!!!\n",recv_buf );
//
		strcpy( end_platform, recv_buf );
*/

		if( ( ret = recv( connect_fd,recv_buf, MAXDATASIZE , 0 ) ) < 0 )
		{
			my_err( "Recv",__LINE__ );
			status = -1;
		}

		printf( "Server Recive  ----  OK \n" );

		int  j = 0, k = 0, l = 0;

		for(; k < 3 ;)
		{
			for(l = 0; recv_buf[ j ] != '#' ;l++, j++) 
			{
				if( k == 0 )
				{
					chooseway[0] = recv_buf[ j ];
					chooseway[1] = '\0';
					chooseWay = atoi(chooseway);
				}
				if( k == 1 )
				{
					start_platform[ l ] = recv_buf[ j ];	
					start_platform[ l+1 ] = '\0';
				}
				if( k == 2 )
				{
					if( recv_buf[ j ] == '$' )
						break;
					end_platform[ l ] = recv_buf[ j ];
					end_platform[ l+1 ] = '\0';
				}
			}
			k++;
			j++;
		}
	//	printf("*%d*%s*%s*\n", chooseWay, start_platform, end_platform);
	

//recive 0 bytes.----means recive nothing

		if( ret == 0 )
		{
			close( connect_fd );
			printf( "Client are disconnected.\n" );
			return;
		}

//status < 0.----means transport has problem
		if( status < 0 )
		{
			strcpy( send_buf, "-1" );
			send( connect_fd, send_buf, strlen( send_buf ), 0 );
		}


		if( status >= 0 )
		{

			
			        struct subway *data[N];

			        read_subway_data(data);

			        strcpy( send_buf, seek_route(end_platform, start_platform, data) );

				send( connect_fd, send_buf, strlen( send_buf ), 0 );

			
		}	
	
//			printf("*%d*%s*%s*\n", chooseWay, start_platform, end_platform);
	close( connect_fd );

}
