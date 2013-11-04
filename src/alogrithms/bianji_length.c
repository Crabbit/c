/*
 * Alogrithms about bianji length
 * --	Dynamic programing
 *
 * File		:	bianji_length.c
 * Time		:	2013-10-21
 * Coder	:	lili
 * Environment	:	linux OS (RHEL 6.0) / gcc 4.4.6
 * 
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<error.h>
#include<fcntl.h>

int	length[32][32];

void my_err( const char *err_string, int line )
{
	fprintf( stderr, "Line : %d\n", line );
	perror( err_string );
	exit( 1 );
}

int MIN( int num1, int num2, int num3 )
{
	if( num1 < num2 )
		if( num1 < num3 )
			return num1;
		else
			return num3;
	else
		if( num2 < num3 )
			return num2;
		else
			return num3;
}

int Diff( char str1, char str2 )
{
	if ( str1 == str2 )
		return 0;
	else
		return 1;
}

int main( int argc, char **argv )
{
//file descriptor
	int		FILE_IN_FD;
	int		FILE_OUT_FD;

	char		*FILE_INPUT="input.txt";
	char		*FILE_OUTPUT="output.txt";

//string1 && string 2
	char		STRING1[32];
	char		STRING2[32];

	char		READ_BUF[2];

	int		i;

	int		m;
	int		n;

	int		STRING1_length = 0;
	int		STRING2_length = 0;

//open file
	if(( FILE_IN_FD = open( FILE_INPUT, O_RDONLY )) == -1 )
		my_err( "Open Failed.",__LINE__ );
	if(( FILE_OUT_FD = open( FILE_OUTPUT, O_RDWR | O_CREAT , 0644 )) == -1)
		my_err( "Open Failed.",__LINE__ );

	printf( "*****************************************\n" );
	printf( "String 1 :" );
	for( i = 0; 1; i++ )
	{
		read( FILE_IN_FD, READ_BUF, 1 );
		STRING1[i] = READ_BUF[0];
		STRING1_length += 1; 

		printf( "%c", STRING1[i] );
		if( STRING1[i] == '\n' )
			break;
	}

	printf( "String 2 :" );
	for( i = 0; 1; i++ )
	{
		read( FILE_IN_FD, READ_BUF, 1 );
		STRING2[i] = READ_BUF[0];
		STRING2_length += 1; 

		printf( "%c", STRING2[i] );
		if( STRING2[i] == '\n' )
			break;
	}
	printf( "*****************************************\n" );

	for( m = 0; m < STRING1_length; m++ )
		length[0][m] = m;

	for( n = 0; n < STRING2_length; n++ )
		length[n][0] = n;

//the most important code
	for( m = 1; m < STRING1_length; m++ )
	{
		for( n = 1; n < STRING2_length; n++ )
			if( STRING1[m-1] != STRING2[n-1] )
//This is the 
				length[n][m] = MIN( length[n-1][m] + 1, length[n][m-1] + 1, length[n-1][m-1] + Diff(STRING1[m-1],STRING2[n-1]));
			else
				length[n][m] = length[n-1][m-1];
	}

//print the table
	for( m = 0; m < STRING2_length; m++ )
	{
		for( n = 0; n < STRING1_length; n++ )
			printf( "%d ", length[m][n] );
		printf( "\n" );
	}

	printf( "*****************************************\n" );
	printf( "The length is %d.\n", length[STRING2_length-1][STRING1_length-1] );

	close( FILE_IN_FD );
	close( FILE_OUT_FD );
	return 0;
}
