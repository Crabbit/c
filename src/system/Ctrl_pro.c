/*
 * =====================================================================================
 *
 *       Filename:  Ctrl_pro.c
 *
 *    Description:  ctrol the process 
 *
 *        Version:  1.0
 *        Created:  10/30/2013 11:02:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Crabbit ( Lili ), lili00681@gmail.com
 *        Company:  Xiyou_linux
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#define MAX_CHILD_NUMBER 10

#define SLEEP_INTERVAL 2

int proc_number = 0;

int main(int argc, char *argv[])
{
	int 	child_proc_number = MAX_CHILD_NUMBER;
	int 	i, ch;
	pid_t 	child_pid;
	pid_t 	pid[10]={0};

	return EXIT_SUCCESS;
}

