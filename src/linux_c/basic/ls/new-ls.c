/*
 * =====================================================================================
 *
 *       Filename:  new-ls.c
 *
 *    Description:  new ls.c
 *
 *        Version:  1.0
 *        Created:  05/18/2014 06:18:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lili, lili00681@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//filetype
enum filetype
{
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
    sock,
    whiteout,
    arg_directory
};

//file information
struct fileinfo
{
    /* The file name.  */
    char *name;
    /* For symbolic link, name of the file linked to, otherwise zero.  */
    char *linkname;

    mode_t linkmode;

    enum filetype filetype;


};

enum sort_type
  {
    sort_none = -1,		/* -U */
    sort_name,			/* default */
    sort_extension,		/* -X */
    sort_size,			/* -S */
    sort_version,		/* -v */
    sort_time,			/* -t */
    sort_numtypes		/* the number of elements of this enum */
  };

static char const *const sort_args[] =
{
  "none", "time", "size", "extension", "version", NULL
};

static enum sort_type const sort_types[] =
{
  sort_none, sort_time, sort_size, sort_extension, sort_version
};


//处理用户参数
int decode_switches( int argc, char *argv[] )
{

}

int main(int argc, char *argv[])
{

	int i;

	i = decode_switches();

	return EXIT_SUCCESS;
}

