/*
 *Copyright (c) Xiyou_linux
 *All rights reserved.
 *
 *File			:	order_file.c
 *Time			:	2012.12.4
 *Editor		:	lili
 *Email			:	lili00681@gmail.com
 *Thanks		:	google && Unix program
 *
 *
 * The is the file module is the part of communicate module.
 * And in this module,include most of operating of the FILE.
 * Like Read--write......
 *
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "order_errno.h"

void COMM_CREATE_FILE( char *FILE_NAME )
{
	int				FILE_ONLINE_fd;

	if( ( FILE_ONLINE_fd = open(  FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH )) == -1 )
		my_err( "Create file / Open",__LINE__ );

	close ( FILE_ONLINE_fd );
}

//save the ip address
int COMM_SAVE_IPADDRESS( char * IP_ADDRESS )
{

//File descriptor -- COMM_FILE_ONLINE
	int                             FILEDS_comm_online_fd;                     
//file format control value,keep the ip address occ 15 bytes.
	int                             FILE_format_control = 0;

	if ( ( FILEDS_comm_online_fd = open( "COMM_FILE_ONLINE", O_APPEND | O_WRONLY)) == -1 )
	{
		pr_err( "Open", errno, strerror( errno ) );
                return ( -1) ;
	}
        
//      save the ip address with the a predetermined format                        
//      write( FILEDS_comm_online_fd, strcat( inet_ntoa( client.sin_addr ),"\n"),strlen( inet_ntoa( client.sin_addr )) );

        if( write( FILEDS_comm_online_fd, IP_ADDRESS, strlen( IP_ADDRESS )) == -1 )
	{
		pr_err( "Write", errno, strerror( errno ) );
                return ( -1) ;
	}


        FILE_format_control = 15 - strlen( IP_ADDRESS );
        for( ; FILE_format_control != 0; FILE_format_control-- )
                write( FILEDS_comm_online_fd, " ", 1 );

        if( write( FILEDS_comm_online_fd, " CONNECTING\n", 12 ) == -1 )
	{
		pr_err( "Write", errno, strerror( errno ) );
                return ( -1) ;
	}
	else
		printf( "connecting save successful\n" );

        close( FILEDS_comm_online_fd );
	return 0;

}

//change the state
int COMM_FILE_STATE_EXCHANGE( char *EXCHANGE_IP )
{
	int				FILE_ONLINE_FD;
	char 				read_file_buf[ 16 ] ;

//file format control value,keep the ip address occ 15 bytes.
	int                             FILE_format_control = 0;

//	int				result = 0;
	int				test;

	if( ( FILE_ONLINE_FD = open( "COMM_FILE_ONLINE", O_RDWR )) == -1 )
	{
		pr_err( "Open", errno, strerror( errno ) );
                return ( -1);
	}

	while ( 1 )
	{
//read 15 bytes 
//		if( read( FILE_ONLINE_FD, read_file_buf, 15 )  == -1 )
		printf( "read_file_buf address = %p\n",&read_file_buf );
		test = read( FILE_ONLINE_FD, read_file_buf, 15 );
		printf( "FILE_ONLINEeFD = %d\n",FILE_ONLINE_FD );
		printf( "read_file_buf address = %p\n",&read_file_buf );
		printf( "read_file_buf = %s\n",read_file_buf );
		printf( "read_file_buf address = %p\n",&read_file_buf );
		printf( "read_file_buf = %s\n",read_file_buf );
		
		printf( "test = %d\n",test );
		if( test == -1 )
		{
			pr_err( "Read", errno, strerror( errno ) );
                	return ( -1);
		}
		else
		{
//check the read fiel with exchange ip
			if( strcmp( read_file_buf, EXCHANGE_IP ) == 0 )
			{
        			FILE_format_control = 15 - strlen( EXCHANGE_IP );
       				for( ; FILE_format_control != 0 ;FILE_format_control-- )
        		       		write( FILE_ONLINE_FD, " ", 1 );

//change the state
				if( write( FILE_ONLINE_FD, " DISCONNECT\n", 12 ) == -1 )
				{
					pr_err( "Write", errno, strerror( errno ) );
                			return ( -1);
				}

        			close( FILE_ONLINE_FD );
				break;
			}
		}

//cheap 12 bytes
		if ( lseek( FILE_ONLINE_FD, 12, SEEK_CUR ) == -1 )
		{
			pr_err( "Lseek", errno, strerror( errno ) );
                	return ( -1);
		}
	}
	return 0;
}
