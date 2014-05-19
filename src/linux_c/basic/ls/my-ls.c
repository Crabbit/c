#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<linux/limits.h>
#include<time.h>

//The funcation : stat ( const char * file_name, struct stat *buf )
//The funcation : lstat( const char *file_name, struct stat *buf )
//The funcation : fstat ( int file_name_fd , struct stat *buf )

void my_err( const char * err_string, int line )
{
	fprintf( stderr, "Line : %d",line );
	perror( err_string );
	exit( 1 );
}

//定义的五个全局变量，用来控制输出格式
int user_maxlen = 0;
int grp_maxlen = 0;
int link_maxlen = 0;
int size_maxlen = 0;
int name_maxlen = 0;


//求出数字是个几位数，方便空格的调整
int qiu_shi( int num )
{
	int i = 0;
	for( i=0; num != 0; )
	{
		num = num/10;
		i++;
	}
	return i;
}

//输出数字格式的函数
void Print_Num_format( int number, int maxlen )
{
	int i = 0 , j = 0;
	
	int len;

	len = qiu_shi( number );
	j = maxlen - len;

	if( maxlen == len )
	printf( " " );
	else
		for( i = 0; i < j; i++  )
			printf( " " );

	printf( "%d",number );

}

//输出字符格式的函数
void Print_char_format( char *character, int maxlen)
{
	int i = 0, j = 0;

	int len;

	len = strlen( character );
	j = maxlen - len;

	for ( i = 0; i < j; i++ )
		printf( " " );

	printf( "%s ", character );
}

void Print_mode( mode_t mode )
{
	int i;

//get the type of the file
	if (S_ISLNK(mode))
                printf("l");
	if (S_ISREG(mode))
                printf("-");
	if (S_ISDIR(mode))
                printf("d");
	if (S_ISCHR(mode))
                printf("c");
	if (S_ISBLK(mode))
                printf("b");
	if (S_ISFIFO(mode))
                printf("f");
	if (S_ISSOCK(mode))
                printf("s");

	printf( " " );

//print User--Group--Other permissions
	for( i = 0; i < 3; i++ )
	{
		if (mode & S_IRUSR)
			printf("r");
		else
			printf("-");
		
		if (mode & S_IWUSR)
			printf("w");
		else
			printf("-");
		
		if (mode & S_IXUSR)
			printf("x");
		else
			printf("-");
		
	}
	printf( " " );

}

//输出所有属性函数
void Print_Z( struct stat buf )
{
	int n;
	
	struct passwd *user_id;
	struct group *group_id;

	char buf_time[32];

	Print_mode( buf.st_mode );

//以下都要考虑格式,所以都是用上面的自定义函数输出信息
	Print_Num_format (buf.st_nlink, link_maxlen );
	printf( " " );

	user_id = getpwuid( buf.st_uid );
	Print_char_format( user_id->pw_name, user_maxlen);

	group_id = getgrgid( buf.st_gid );
	Print_char_format( group_id->gr_name, grp_maxlen);

	Print_Num_format( buf.st_size, size_maxlen );

	strcpy( buf_time, ctime( &buf.st_mtime ) );
	buf_time[ strlen( buf_time ) - 1 ] = '\0';
	printf( "  %s    ~~ lili ~~   ", buf_time );
}

void Print( int value, char *filename )
{
	int 		i,j;


	if( value == 6 )
	{
//value == 2 或 4 时，就要收集文件属性信息，并输出
		struct stat 	buf;

		if( lstat( filename, &buf ) == -1 )
			my_err( "Stat",__LINE__ );

		Print_Z( buf );
		printf( "%s\n", filename );
	}

	if( value == 4 )
	{
		printf( "%s        ", filename );
	}

	if( value == 2 )
	{
		struct stat 	buf;

		if( lstat( filename, &buf ) == -1 )
			my_err( "Stat",__LINE__ );

		if( filename[ 0 ] != '.' )
		{
			Print_Z( buf );
			printf( "%s\n", filename );
		}
		
	}

	if( value != 2 && value != 4 && value != 6)
	{
		if( filename[ 0 ] != '.' )
			printf( "%s        ", filename );
	}

}

//统计函数
void Statics( char *filename )
{
	struct stat 	buf;

	struct passwd *user_id;
	struct group *group_id;

	if( lstat( filename, &buf ) == -1 )
		my_err( "Stat",__LINE__ );

	user_id = getpwuid( buf.st_uid );
	group_id = getgrgid( buf.st_gid );

	if( name_maxlen < strlen( filename ) )
		name_maxlen = strlen( filename );

	if( user_maxlen < strlen( user_id->pw_name ) )
		user_maxlen = strlen( user_id->pw_name );

	if( grp_maxlen < strlen( group_id->gr_name ) )
		grp_maxlen = strlen( group_id->gr_name );

	if( link_maxlen < qiu_shi( buf.st_nlink ) )
		link_maxlen = qiu_shi( buf.st_nlink );

	if( size_maxlen < qiu_shi( buf.st_size ) )
		size_maxlen = qiu_shi( buf.st_size );
}

//输出目录的总函数
void Print_dir( int value, char *Input_Name[] )
{
	DIR	*dir;
	struct dirent	*dir_file;

	int i;

/*	int 	count = 0;

//定义一共可以存储256个文件名，并且变量的长度为最长的那个文件名
	char	filename[512][PATH_MAX+1],temp[PATH_MAX+1];
*/	

//打开输入的目录，通过循环获取 文件个数 以及 最大长的文件名长度，用来 控制循环 和 划分变量
	for( i = 0; Input_Name[ i ]  != NULL; i++ )
	{
		dir = opendir( Input_Name[i] );

		if( dir == NULL )
			my_err( "Opendir",__LINE__ );

//为保证输出格式，统计目录下所有文件信息
		while( ( dir_file = readdir( dir ) ) != NULL )
			Statics( dir_file->d_name );
		closedir( dir );

		char	*DIR_NAME[name_maxlen];
//输出信息,需要重新打开一次目录
		dir = opendir( Input_Name[ i ] );
			while( ( dir_file = readdir( dir ) ) != NULL )
			{

/*		if( g_maxlen < strlen ( dir_file->d_name ) )
			g_maxlen = strlen( dir_file->d_name );
		count++;
*/

				Print( value, dir_file->d_name );
			}

//单独为这两种情况换行
		if( value != 2 && value !=6 )
			printf( "\n" );
		closedir( dir );
	}

/*
//如果文件个数大于512，就报错。
	if( count > 512 )
		my_err( "Too many files under this dir",__LINE__ );

	int	 i, j;
	int	 len = strlen( Input_Name[0] );
	
//	dir = opendir( Input_Name[0] );
	

//获取目录下的所有文件名,并保存在变量  --  filename[ ][ ]中
	for( i = 0; i < count; i++ )
	{
		dir_file = readdir( dir );

		if( dir_file == NULL )
			my_err( "Readdir",__LINE__ );
		
//每个文件名前面标识目录名

		strncpy( filename[i], Input_Name[0], len );
		filename[ i ][ len ] = '\0';
		strcat( filename[i], dir_file->d_name );
		filename[ i ][ len+strlen( dir_file->d_name ) ] = '\0';

	}
	
	closedir( dir );

//用来将刚刚的信息输出
	for( i= 0; i < count; i++ )
		Print( value, filename );
	

	if( value != 2 ) 
		printf( "\n" );
*/

}

int main( int argc, char **argv )
{	
	struct stat buf;
	int value = 0;
	char *Input_Name[128] = { NULL };
	int m=0, n=0, l=0;
	int i = 0;

//判断参数以及文件名
	if(argc >= 2)
	{
		for( m = 1; m < argc; m++ )
			for( n = 0; argv[m][n] != '\0'; n++ )
			{
//以-为检查符号
				if( argv[m][n] == '-' )
				{
					for( n = n+1; argv[m][n] != '\0'; n++ )
					{
						if( argv[m][n] != 'a' && argv [m][n] != 'l' )
							printf( "invalid option --%c\n",argv[m][n] );
		
						if( argv[m][n] == 'a' )
							value = value + 4;
						
						if( argv[m][n] == 'l' )
							value = value + 2;
					}
					break;			//跳出当前参数，选择下一个参数
				}

				else
				{
					Input_Name[l] = argv[m];
					l++;
					break;			//跳出当前字符，来查询下一个字符
				}
			}
	}
	
	if ( Input_Name[ 0 ] == NULL )
		Input_Name[0] = "./";
	Print_dir( value, Input_Name );
/*	if( Input_Name[ 0 ] != NULL )
		for( i = 0; i < argc - 1; i++ )
		{
			printf( "%s : \n",Input_Name[ i ] );
			Print_dir( value, Input_Name );
		}
*/
	return 0;
}
