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

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

typedef enum {false = 0, true = 1} bool;

//filetype
enum Filetype
{
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
};

//显示时间类型 
enum Time_type
{
    //default 最后修改时间 
    time_mtime,

    //-c 最后状态改变时间
    time_ctime,

    //-u 最后访问时间
    time_atime
};
static enum Time_type time_type;

//隐藏/非隐藏模式
static enum Ignore_mode
{
  /* Ignore files whose names start with `.', and files specified by
     --hide and --ignore.  */
  IGNORE_DEFAULT,

  // ..
  IGNORE_DOTDOT,

  /* Ignore only files specified by --ignore.  */
  IGNORE_MINIMAL
}ignore_mode = IGNORE_DEFAULT;

//输出格式
enum Format
{
    default_format,
    long_format
};
static enum Format format ;

//file information
typedef struct fileinfo
{
    //链接数
    nlink_t file_nlink;
    //文件类型和权限
    mode_t file_mode;
    //UID
    uid_t file_uid;
    //GID
    gid_t file_gid;
    //所占字节数
    off_t file_size;
    //default 最后修改时间 
    time_t file_mtime;
    //-c 最后状态改变时间
    time_t file_ctime;
    //-u 最后访问时间
    time_t file_atime;
    /* The file name.  */
    char *file_name;
}Fileinfo;

//递归/非递归
static bool recursive;

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

//Fileinfo * get_dir( char const *name ,enum Ignore_mode ignore_mode );
Fileinfo * get_dir( char const *name );
void print_result( Fileinfo *file_array, enum Ignore_mode ignore_mode, enum Format format, enum Time_type time_type, bool recursive );

int main(int argc, char *argv[])
{

	//非递归
	recursive = false;
	//默认格式
	format = default_format;
	//默认时间
	time_type = time_mtime;
	//隐藏模式
	ignore_mode = IGNORE_DEFAULT;

	//接受处理的变量
	int result;
	//获取处理后文件数组首地址
	Fileinfo *file_array;

	//getopt不输出错误信息到stderr
	opterr = 0;

	//默认情况下，dirname是dot - .
	char dirname[32] = {0};
	strncpy( dirname, ".", 1 );

	while(( result = getopt(argc, argv, "al:R:u:") ) != -1 )
	{
		printf( "result = %d - %c.\n", result, result );
		switch(result)
		{
			case 'a':
				printf( "option = a\n." );
				ignore_mode = IGNORE_MINIMAL;
				break;
			case 'l':
				//printf( "option = l, optarg = %s\n.", optarg );
				format = long_format;
				break;
			case 'R':
				//printf( "option = R, optarg = %s\n.", optarg );
				recursive = true;
				break;
			case 'u':
				//printf( "option = u, optarg = %s\n.", optarg );
				time_type = time_atime;
				break;
			//处理未定义的参数
			case '?':
				printf( "ls: %c: invalid option\n", optopt );
				printf( "ls: usage: ls [-a|-l|-R|-u] [file|dir]" );
				break;
			//不带参数
			default:
				printf( "NO option.\n" );
				break;
		}
	}
	file_array = get_dir( dirname );
	print_result( file_array, ignore_mode, format, time_type, recursive );
	return EXIT_SUCCESS;
}

//static void print_dir( char const *name, char const *realname, bool command_line_arg )
//Fileinfo * get_dir( char const *name ,enum Ignore_mode ignore_mode , bool recursive )
Fileinfo * get_dir( char const *name )
{
	//统计文件个数
	int count = 0;

	//读取目录
	DIR *dirp;
	struct dirent *next;

	//定义动态数组
	//存取目录文件信息
	Fileinfo *file_array;

	//获取文件详细信息
	struct stat buf;

	//申请动态数组首地址
	file_array = (Fileinfo *)malloc( sizeof(Fileinfo) );

	dirp = opendir( name );
	if( !dirp )
	      fprintf( stderr, "lsl:cannot open directory %s.\n", name );
	else
	{
		while((next = readdir( dirp )) != NULL )
		{
			file_array = (Fileinfo *)realloc( file_array, (count + 1) * sizeof(Fileinfo));
			if( lstat( next->d_name, &buf ) == -1 )
			      fprintf( stderr, "lstat error.\n" );
			file_array[count].file_mode = buf.st_mode;
			file_array[count].file_nlink = buf.st_nlink;
			file_array[count].file_uid = buf.st_uid;
			file_array[count].file_gid = buf.st_gid;
			file_array[count].file_size = buf.st_size;
			file_array[count].file_mtime = buf.st_mtime;
			file_array[count].file_atime = buf.st_atime;
			file_array[count].file_ctime = buf.st_ctime;
			file_array[count].file_name = next->d_name;
			file_array[count].file_name = next->d_name;
			//printf( "%s\n",next->d_name );
			//printf( "%s\n", file_array[count].file_name );
		      	count++;
		}
		printf( "Total %d file.\n", count );
	}

	closedir( dirp );
	return file_array;
}

void print_result( Fileinfo *file_array, enum Ignore_mode ignore_mode, enum Format format, enum Time_type time_type, bool recursive )
{
	if( ignore_mode == IGNORE_DEFAULT )
	{

	}

}
