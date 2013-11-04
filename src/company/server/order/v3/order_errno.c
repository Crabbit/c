/*
 * Copyright (c) Xiyou_linux                                                       
 * All rights reserved.                                                            
 *
 *File                  :       order_errno.c
 *Time                  :       2012.12.4
 *Editor                :       Lili
 *Email                 :       lili00681@gmail.com
 *Thanks                :       google && ssl ...
 *
 *This is the errno module.
 *In this part ,include some handle error function.
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//handle errno with exit
void my_err( const char *err_string,int line );

void my_err( const char *err_string,int line )
{
        fprintf( stderr,"line : %d .\n",line );
        perror( err_string );
        exit( 1 );
}

void pr_err( char *err_string,int error_code, char * err_info )
{
	printf( "%s ERROR. Error code : %d. Error info : %s .\n",err_string, error_code, err_info );
}
