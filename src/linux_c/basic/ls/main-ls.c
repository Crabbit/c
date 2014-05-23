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
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#include <pwd.h>
#include <grp.h>

#include <sys/ioctl.h>

typedef enum {false = 0, true = 1} bool;

//file amount
static int count;

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

static enum sort_type const sort_types[] =
{
  sort_none, sort_time, sort_size, sort_extension, sort_version
};

//Fileinfo * get_dir( char const *name ,enum Ignore_mode ignore_mode );
Fileinfo * get_dir( char const *name );
void print_result( Fileinfo *file_array, enum Ignore_mode ignore_mode, enum Format format, enum Time_type time_type, bool recursive );
void Print_mode( mode_t mode, char str[]);
int get_num_length( int number );
int max( int x, int y );
void print_suit_num( int num, int max_length );
void print_suit_char( char *str, int max_length );
void print_time( time_t time );
void  recursive_pend( char const *dirname );
int comp (const void *x, const void *y);
void my_sort ( Fileinfo *file_array );

void my_err( const char *err_string, int line )
{
	fprintf( stderr, "line:%d", line );
	perror( err_string );
	exit(1);
}

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

	while(( result = getopt(argc, argv, "aluR") ) != -1 )
	{
		//printf( "result = %d - %c.\n", result, result );
		switch(result)
		{
			case 'a':
				//printf( "option = a\n." );
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
	if( recursive == false )
	{
		file_array = get_dir( dirname );
		print_result( file_array, ignore_mode, format, time_type, recursive );
	}
	else
	{
		recursive_pend( dirname );
	}
	return EXIT_SUCCESS;
}

void  recursive_pend( char const *dirname )
{
	//递归处理文件
	Fileinfo *file_recu;
	//获取处理后文件数组首地址
	Fileinfo *file_array;

	//控制递归变量
	int control_recu = 0;

	//通过这个取出文件是否是目录 
	char str[10];

	//递归深层目录
	char dir_deep[256];
	//当前目录文件数
	int count_recu = 0;

	//printf( "dir_deep : %s\n", dirname );
	printf( "\n" );
	printf( "Directory : %s\n", dirname );
	file_array = get_dir( dirname );
	count_recu = count;
	print_result( file_array, ignore_mode, format, time_type, recursive );

	//开始对目录做递归处理
	//用新变量对当前目录做操作
	file_recu = file_array;
	//开始循环检查
	for( control_recu = 0; control_recu < count_recu ; control_recu++)
	{
		//始终保持在当前目录下
		strcpy( dir_deep, dirname );
		//printf( "In -> %s The %d file -> %s\n", dir_deep, control_recu, file_array[control_recu].file_name );
		if( (ignore_mode == IGNORE_MINIMAL)
					|| (ignore_mode == IGNORE_DEFAULT) 
					&& (strncmp(file_array[control_recu].file_name, "..", 1 ) != 0) )
		{
			Print_mode( file_array[control_recu].file_mode, str );
			if( (strncmp(str, "d", 1) == 0) 
				&& ( strcmp(file_recu[control_recu].file_name, "." )!=0 ) 
				&& ( strcmp(file_recu[control_recu].file_name, ".."  )!= 0 ))
			{
				//printf( "----directory name is :%s\n", file_array[control_recu].file_name );
				//在目录后添加/
				strcat( dir_deep, "/" );
				strcat( dir_deep, file_array[control_recu].file_name  );
				//printf( "dir is %s\n", dirname );
				recursive_pend( dir_deep );
			}
		}
	}
}

//static void print_dir( char const *name, char const *realname, bool command_line_arg )
//Fileinfo * get_dir( char const *name ,enum Ignore_mode ignore_mode , bool recursive )
//获取指定目录下的各个信息
Fileinfo * get_dir( char const *name )
{
	//统计文件个数
	count = 0;

	//读取目录
	DIR *dirp;
	struct dirent *next;

	//获得目录名称
	char str[256];

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
			file_array = (Fileinfo *)realloc( file_array, (count + 2) * sizeof(Fileinfo));
			
			strcpy( str, name );
			strcat( str, "/" );
			strcat( str, next->d_name );
			//printf( "lstat file is %s\n", str);
			if( lstat( str, &buf ) == -1 )
				my_err( "lstat",__LINE__ );
			file_array[count].file_mode = buf.st_mode;
			file_array[count].file_nlink = buf.st_nlink;
			file_array[count].file_uid = buf.st_uid;
			file_array[count].file_gid = buf.st_gid;
			file_array[count].file_size = buf.st_size;
			file_array[count].file_mtime = buf.st_mtime;
			file_array[count].file_atime = buf.st_atime;
			file_array[count].file_ctime = buf.st_ctime;
			file_array[count].file_name = next->d_name;
			//printf( "%s\n",next->d_name );
			//printf( "%s\n", file_array[count].file_name );
		      	count++;
		}
		//printf( "Total %d file.\n", count );
	}

	my_sort( file_array );

	closedir( dirp );
	return file_array;
}

void print_result( Fileinfo *file_array, enum Ignore_mode ignore_mode, enum Format format, enum Time_type time_type, bool recursive )
{

	//通过全局变量count，获得当前目录文件数量.
	//通过amount控制
	int amount;
	//通过total获得处理的总文件数
	int total = 0;

	//控制linke最大数
	unsigned max_link = 1;
	//获得用户名最长个数
	unsigned max_name = 1;
	//获得组名最长个数
	unsigned max_group = 1;
	//控制size最大数
	unsigned max_size = 1;

	//输出权限的字符串
	char str[10];

	struct passwd *user_id;
	struct group *group_id;

	//获取终端大小
	struct winsize ws;
	//最大可能将屏幕分256栏,用来记录每栏最大宽度
	int block_length[256] = {0};
	//用来记录一共多少栏
	int block_num = 0;
	//文件名最短检测
	int min_name_length = 50;
	//当前最大总长度
	int max_sum_length = 0;
	//控制实际输出到第几列,而不是用文件数量变量控制
	int control_ana = 0;
	//控制输出空格数量
	int space_num = 0;

	if( ioctl( 0, TIOCGWINSZ, &ws ) != 0 )
	      fprintf( stderr, "ioctl error.\n" );


	////先处理一遍文件，求出链接数啊等等最大值
	for( amount = 0; amount < count; amount++ )
	{
		//要么-a非隐藏，要么隐藏模式+隐藏dot.
		if( (ignore_mode == IGNORE_MINIMAL)
					|| (ignore_mode == IGNORE_DEFAULT) 
					&& (strncmp(file_array[amount].file_name, "..", 1 ) != 0) )
		{
			//处理文件数自加
			total++;
			//求链接数数字长度最大值
			max_link = max( get_num_length(file_array[amount].file_nlink), max_link );
			//求用户名最长值
			user_id = getpwuid( file_array[amount].file_uid );
			max_name = max( strlen(user_id->pw_name), max_name );
			//求组名最长值
			group_id = getgrgid( file_array[amount].file_gid );
			max_group = max( strlen(group_id->gr_name), max_group );
			//求size最大值
			max_size = max( get_num_length(file_array[amount].file_size), max_size );

			if( (strlen(file_array[amount].file_name)+2) < min_name_length )
			      min_name_length = strlen(file_array[amount].file_name)+2;

		}
	}

	//通过屏幕宽度，根据最小文件名长度计算最大分多少列
	//printf( "clo = %d, min length = %d.\n", ws.ws_col, min_name_length );
	block_num = ws.ws_col / min_name_length;

	//开始计算分栏
	//当文件大于block_length[]中记录时候，block_num - 1
	//并重新计算栏宽
	//printf( "total %d lie.\n", block_num );

	//求出小列宽度，最多列情况下，每一列的最长长度
	while( 1 )
	{
		for( amount = 0, control_ana = 0; amount < count; amount++)
		{
			if( (ignore_mode == IGNORE_MINIMAL)
						|| (ignore_mode == IGNORE_DEFAULT) 
						&& (strncmp(file_array[amount].file_name, "..", 1 ) != 0) )
			{
				//printf( "now exec is %d lie.\n",control_ana%block_num );
				if( (strlen( file_array[amount].file_name )+2) > block_length[control_ana%block_num] )
				{
					block_length[control_ana%block_num] = strlen( file_array[amount].file_name ) +2;
				}
				//printf( "%d lie -- file %s,lie length is %d.\n", control_ana%block_num, file_array[amount].file_name, block_length[control_ana] );
				control_ana++;
			}
		}
		for( amount = 0, max_sum_length = 0; (amount < total) && (amount < block_num); amount++ )
		{
		      max_sum_length += block_length[amount];
		}
		if( max_sum_length > ws.ws_col )
		      block_num--;
		else
		      break;
		//printf( "Now block_number is :%d.\n", block_num );
	}

	//printf( "total %d lie.\n", block_num );
	printf( "Total %d files.\n", total );
/*
	printf( "max link is %d.\n", max_link );
	printf( "max name is %d.\n", max_name );
	printf( "max grop is %d.\n", max_group );
	printf( "max size is %d.\n", max_size );
*/

	//开始显示文件
	for( amount = 0; amount < count; amount++ )
	{
		if( (ignore_mode == IGNORE_MINIMAL)
					|| (ignore_mode == IGNORE_DEFAULT) 
					&& (strncmp(file_array[amount].file_name, "..", 1 ) != 0) )
		{
			//printf( "file name = %s\n",file_array[amount].file_name );
			//长格式输出
			if( format == long_format )
			{
				Print_mode( file_array[amount].file_mode, str );
				printf( "%-11s", str );
				//输出链接数
				print_suit_num( file_array[amount].file_nlink, max_link );
				//根据uid输出用户名
				user_id = getpwuid( file_array[amount].file_uid );
				print_suit_char( user_id->pw_name, max_name );
				//更具gid输出组名
				group_id = getgrgid( file_array[amount].file_gid );
				print_suit_char( group_id->gr_name, max_group );
				//输出size
				print_suit_num( file_array[amount].file_size, max_size );
				//输出时间
				// -u参数，显示的是最后访问时间
				if( time_type == time_atime )
					print_time( file_array[amount].file_atime );
				else
					print_time( file_array[amount].file_mtime );
				//输出文件名
				printf( "%s\n", file_array[amount].file_name );

				// 默认参数，显示的是最后修改时间
			}
			if( format == default_format )
			{
				for( amount = 0, control_ana = 0; amount < count; amount++ )
				{
					if( (ignore_mode == IGNORE_MINIMAL)
								|| (ignore_mode == IGNORE_DEFAULT) 
								&& (strncmp(file_array[amount].file_name, "..", 1 ) != 0) )
					{
						for( space_num = 0; 
						     space_num <( block_length[control_ana%block_num] - strlen(file_array[amount].file_name) -2 );
						     space_num++ )
						{
							printf( " " );
						}
						control_ana++;
						printf( "%s  ", file_array[amount].file_name );
					}
					if( control_ana != 0 && control_ana % block_num == 0 )
					      printf( "\n" );
				}
				printf( "\n" );
			}
		}
	}
}

void Print_mode( mode_t mode, char str[])
{
	strcpy( str, "----------" );
//get the type of the file
	if (S_ISLNK(mode))
                str[0] = 'l';
	if (S_ISREG(mode))
                str[0] = '-';
	if (S_ISDIR(mode))
                str[0] = 'd';
	if (S_ISCHR(mode))
                str[0] = 'c';
	if (S_ISBLK(mode))
                str[0] = 'b';
	if (S_ISFIFO(mode))
                str[0] = 'f';
	if (S_ISSOCK(mode))
                str[0] = 's';

//print User--Group--Other permissions
	if (mode & S_IRUSR)
		str[1] = 'r';
	if (mode & S_IWUSR)
		str[2] = 'w';
	if (mode & S_IXUSR)
		str[3] = 'x';
	if (mode & S_ISUID)
	        str[3] = 's';
	if (mode & S_IRGRP)
		str[4] = 'r';
	if (mode & S_IWGRP)
		str[5] = 'w';
	if (mode & S_IXGRP)
		str[6] = 'x';
	if (mode & S_ISGID)
		str[6] = 's';
	if (mode & S_IROTH)
		str[7] = 'r';
	if (mode & S_IWOTH)
		str[8] = 'w';
	if (mode & S_IXOTH)
		str[9] = 'x';
	if (mode & S_ISVTX)
		str[9] = 't';
}

//求出数字多长
int get_num_length( int number )
{
	//记录几位数
	int i = 1;
	//处理传入数字
	int tmp = number;
	//求得i为位数
	for( i = 0; tmp != 0 ;i++  )
	      tmp /= 10;
	return i;
}

int max( int x, int y )
{
	return x>y?x:y;
}

//输出合适格式的数字
void print_suit_num( int num, int max_length )
{
	int num_length = 0;
	if( num != 0 )
		num_length = get_num_length( num );
	else
		num_length = 1;
	for( ; (max_length - num_length) != 0; num_length++  )
	      printf( " " );

	printf( "%d", num );
	//最后面补上一个空格
	printf( " " );
}

//输出合适格式的字符串
void print_suit_char( char *str, int max_length )
{
	int char_length = 0;
	char_length = strlen( str );
	//字符串先输出，再输出空格
	printf( "%s", str );

	for( ;(max_length - char_length) != 0 ; char_length++ )
	      printf( " " );

	//最后面补上一个空格
	printf( " " );
}

//输出时间
void print_time( time_t time )
{
	int i = 0;
	char buf_time[32];

	strncpy( buf_time, ctime(&time),24 );
	buf_time[25] = '\0';

	for( i = 4; i < 16; i++ )
		printf( "%c", buf_time[i] );
	printf( " " );
}

// qsort函数
int comp (const void *x, const void *y)
{
	return strcmp(((Fileinfo*)x)->file_name, ((Fileinfo*)y)->file_name);
}

void my_sort ( Fileinfo *file_array )
{
	qsort (file_array, count, sizeof (Fileinfo), comp);
}
