#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include"mysql.h"

#define MAX_VERTEX_NUM	100
#define INFINITY	101   //最大的权
#define MAX_NUM		20000
#define FALSE		0
#define	TRUE		1

MYSQL   my_connection;
MYSQL_RES       *res_ptr;
MYSQL_ROW       sqlrow;

typedef struct{

	int	quan;		//边上的权值
	int	minNum;		//此边上站的最小编号
	int	maxNum;		//此边上站的最大编号
	int	CourseXian[3];	//此边经过的线
}border;
typedef struct{

	int	num;		//顶点的编号
	int	FlatformNum;	//顶点站的编号
	int	CourseXian[7];	//顶点经过的线
}ver;
typedef struct{

	ver	vertex[MAX_VERTEX_NUM];			//顶点信息
	border	edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//边的信息
	int	n, e;					//顶点试和边数
}MGraph;

int	D[MAX_VERTEX_NUM];
int	TruePath[MAX_VERTEX_NUM];
int	flag = 0;
char 	resultInfo1[100][40], resultInfo2[80][40];
int	resultK = 0;

int ReadFile(char *FILE_NAME, char ArcArray[10][50], int *PointPosition);
void CreateGraph(MGraph *G, int biao);
void rideWay(MGraph *G, int *TruePath, int v1);
void addAPoint(MGraph *G, int *v);
char * readPlatformName(int * num, char *platform);
int coursePlatform(MGraph *G, int *TruePath, int v1);
void subwayRoute(MGraph *G, int v0, int v1, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int *OrderPath);
void ShortTestPath(MGraph *G, int v0, int v1, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM]);

int ReadFileSQL(int biao)
{
        int     res;

        mysql_init(&my_connection);
        if(!mysql_real_connect(&my_connection,"localhost","root","subway","subway",0,NULL,0))
                return -1;
        switch(biao)
        {
                case  21:
                        res=mysql_query(&my_connection,"SELECT * FROM subway1");	break;
                case  1:
                        res=mysql_query(&my_connection,"SELECT * FROM subway2");	break;
                case  3:
                        res=mysql_query(&my_connection,"SELECT * FROM subway3");	break;
                case  2:
                        res=mysql_query(&my_connection,"SELECT * FROM subway4");	break;
                case  10:
                        res=mysql_query(&my_connection,"SELECT * FROM subway5");	break;
                case  11:
                        res=mysql_query(&my_connection,"SELECT * FROM subway6");	break;
                case  12:
                        res=mysql_query(&my_connection,"SELECT * FROM subway7");	break;
	}
        if(res)
                return -1;
        res_ptr=mysql_store_result(&my_connection);
        if(!res_ptr)
                return -1;

        return 0;
}
void ShortTestPath(MGraph *G, int v0, int v1, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	int	v, w, i, j, min, k = 1, OrderPath[MAX_VERTEX_NUM], final[MAX_VERTEX_NUM] = {0};

	for(v = 0; v<G->n; v++){

		final[v] = FALSE;	//初始化final列表
		D[v] = G->edge[v0][v].quan;
		for(w = 0; w<G->n; w++)
			P[v][w] = FALSE;	//初始化P数组
		if(D[v] < INFINITY)	
			P[v][v0] = TRUE, P[v][v] = TRUE;	//如果V0 可以直接到达V 则，在P中标记
	}

	D[v0] = 0, final[v0] = TRUE;
	for(i=1; i<G->n; i++){

		min = INFINITY;
		for(w = 0; w<G->n; w++)
			if(final[w] == FALSE)
				if(D[w] < min){		//找到距离V0最近的点

					v = w;
					min = D[w];
				}
		final[v] = TRUE;	//标记已经找到的点
		for(w = 0; w<G->n; w++)
			if(!final[w] && (min + G->edge[v][w].quan < D[w])){

				D[w] = min + G->edge[v][w].quan;
				for(j = 0; j<G->n; j++)		//更新当前路径
					P[w][j] = P[v][j];
				P[w][w] = TRUE;
				OrderPath[k++] = v;	//记录更新的前一个点
			}
	}
	OrderPath[0] = v0, OrderPath[k] = v1, OrderPath[k+1] = -1;
	subwayRoute(G, v0,  v1, P, OrderPath);
}
void rideWay(MGraph *G, int *TruePath, int v1)
{
	int	i=0, j, pre, lat, k0 = 0, k1, m, n;
	char	platformName[40], buf[15];

	resultK = 0;
	while(TruePath[i] != v1){

		pre = G->vertex[TruePath[i]].num, lat = G->vertex[TruePath[i+1]].num;
		if(!G->edge[TruePath[i]][TruePath[i+1]].CourseXian[1])
			k1 = G->edge[TruePath[i]][TruePath[i+1]].CourseXian[0];
		else{
	
			j = i;
			while(1){

				m =  G->vertex[TruePath[j]].num, n =  G->vertex[TruePath[j+1]].num;
				j += 1;
				if((G->edge[m][n].CourseXian[0]!=G->edge[pre][lat].CourseXian[0]) || (G->edge[m][n].CourseXian[1]!=G->edge[pre][lat].CourseXian[1])){

					k1 = G->edge[m][n].CourseXian[0];
					break ;
				}
			}
		}
		if(k0 != k1 && k1){

			readPlatformName(&G->vertex[TruePath[i]].FlatformNum, platformName);	
			strcpy(resultInfo2[resultK++], platformName);
			strcpy(platformName, "-(乘");
			sprintf(buf, "%d", k1);
			strcat(platformName, buf);
			strcat(platformName, "号线)->");
			strcpy(resultInfo2[resultK++], platformName);
		}
		k0 = k1, i++;
	}
	readPlatformName(&G->vertex[TruePath[i]].FlatformNum, platformName);
	strcpy(resultInfo2[resultK++], platformName);
	strcpy(resultInfo2[resultK++], "-1");
}
void subwayRoute(MGraph *G, int v0, int v1, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int *OrderPath)
{
	int	i, j = 0, k, PathNum[MAX_VERTEX_NUM];

	if(D[v1] >= MAX_NUM){

		flag = 1;
		return ;
	}
	for(i = 0; i<G->n; i++)
		if(P[v1][i])
			PathNum[j++] = i;	//记录实际要经过的路径
	PathNum[j] = -1;

	for(i=0, k=0; OrderPath[i]!=v1; i++)	//根据记录的两个路径得到 从V0到V1要走的路线
		for(j=0; PathNum[j]!=-1; j++)
			if(PathNum[j] == OrderPath[i]){

				TruePath[k++] = PathNum[j];
				PathNum[j] = -2;	//避免后边重复输出路径  已经取过的点变为-2
			}
	TruePath[k] = v1;
}
int coursePlatform(MGraph *G, int *TruePath, int v1)
{
	int	i = 0, j, min, max, m, n;
	char	platformName[40];

	resultK = 0;
	while(TruePath[i] != v1){

		m = TruePath[i], n = TruePath[++i];
		min = G->edge[m][n].minNum, max = G->edge[m][n].maxNum;
		readPlatformName(&G->vertex[m].FlatformNum, platformName);
		strcpy(resultInfo1[resultK++], platformName);

		if(min!=MAX_NUM && min && max!=MAX_NUM && max){

			if(min < max)
				for(j = min; j <= max; j++){

					readPlatformName(&j, platformName);
					strcpy(resultInfo1[resultK++], platformName);
				}
			if(min >= max)
				for(j = min; j >= max; j--){

					readPlatformName(&j, platformName);
					strcpy(resultInfo1[resultK++], platformName);
				}
		}
	}
	readPlatformName(&G->vertex[TruePath[i++]].FlatformNum, platformName);
	strcpy(resultInfo1[resultK++], platformName);
	sprintf(platformName, "%d", D[v1]+1);
	strcat(platformName, "站");
	strcpy(resultInfo1[resultK++], platformName);
	strcpy(resultInfo1[resultK], "-1");
}
char * readPlatformName(int *num, char *platform)
{
        int     k, m, n, PointPosition = 0, f = 0;
        int     field_count = 0;
        char    buf[5], array[2][40];


        m = 1, n = 0;         //根据站名读序号
	strcpy(buf, platform);
        if(*num != -1){

		sprintf(buf, "%d", *num);
                m = 0, n = 1;           //根据序号读站名
	}
        ReadFileSQL(21);           //读站名和站编号
        while(sqlrow = mysql_fetch_row(res_ptr)){

        	field_count = 0;
        	while(field_count < mysql_field_count(&my_connection)){

			strcpy(array[0], sqlrow[field_count++]);
			strcpy(array[1], sqlrow[field_count++]);
		}
		if(!strcmp(buf, array[m])){

			if(!m){

				mysql_free_result(res_ptr);
				mysql_close(&my_connection);
				return strcpy(platform, array[n]);
			}
			else{
				*num = atoi(array[0]); return 0;
			}
		}
	}
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);

	return strcpy(platform, "-1");
}
void CreateGraph(MGraph *G, int biao)
{
	int 	i, j, k, m, n;
	unsigned int field_count = 0;

	ReadFileSQL(biao++);
        while(sqlrow = mysql_fetch_row(res_ptr))		//顶点数和边数 顶点序号头尾
       	{
		field_count = 0;
		while(field_count < mysql_field_count(&my_connection)){

	                G->n = atoi(sqlrow[field_count++]);
        	        G->e = atoi(sqlrow[field_count++]);
	                m = atoi(sqlrow[field_count++]);
        	        n = atoi(sqlrow[field_count++]);
		}
	}
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);

	ReadFileSQL(biao++), i = m;
      	while(sqlrow = mysql_fetch_row(res_ptr)){		//顶点信息

		field_count = 0;
		while(field_count < mysql_field_count(&my_connection)){

			G->vertex[i].num = i, G->vertex[i].FlatformNum = atoi(sqlrow[field_count++]);
			for(j = 0; field_count < mysql_field_count(&my_connection); j++)
				G->vertex[i].CourseXian[j] = atoi(sqlrow[field_count++]);
			G->vertex[i].CourseXian[j] = -1, i++;
		}
	}
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);

	for(i = 0; i < G->n; i++)
		for(j = 0; j < G->n; j++){
							//将每一点的权值初始化为无穷大
			G->edge[i][j].quan = MAX_NUM;
			G->edge[i][j].minNum = G->edge[i][j].maxNum = 0;
			G->edge[i][j].CourseXian[0] = G->edge[i][j].CourseXian[1] = 0;
		}

	ReadFileSQL(biao++);
	while(sqlrow = mysql_fetch_row(res_ptr)){       //边对应两个顶点的序号 边的信息

			field_count = 0;
			while(field_count < mysql_field_count(&my_connection)){

				m = atoi(sqlrow[field_count++]);
				n = atoi(sqlrow[field_count++]);
				G->edge[n][m].quan = G->edge[m][n].quan = atoi(sqlrow[field_count++]);
				G->edge[n][m].maxNum=G->edge[m][n].minNum=atoi(sqlrow[field_count++]);
				G->edge[n][m].minNum = G->edge[m][n].maxNum = atoi(sqlrow[field_count++]);
				G->edge[n][m].CourseXian[0] = G->edge[m][n].CourseXian[0] = atoi(sqlrow[field_count++]);
				G->edge[n][m].CourseXian[1] = G->edge[m][n].CourseXian[1] = atoi(sqlrow[field_count++]);
			}
		}
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);
}
void addAPoint(MGraph *G, int *v)
{
	int	i, j, k, min, max, m, n;

	G->vertex[G->n].FlatformNum = *v, G->vertex[G->n].num = G->n;
	G->vertex[G->n].CourseXian[0] = G->vertex[G->n].CourseXian[1] = 0; //添加顶点信息
	G->n += 1, G->e += 1;		//边和顶点数都加1

	for(i = 0; i < G->n; i++){	//初始化

		G->edge[G->n-1][i].quan = G->edge[i][G->n-1].quan = MAX_NUM;
		G->edge[G->n-1][i].minNum = G->edge[G->n-1][i].maxNum = 0;
		G->edge[G->n-1][i].minNum = G->edge[G->n-1][i].maxNum = 0;
	}
		
	for(i = 0; i < G->n - 1; i++)
		for(j = 0; j < G->n - 1; j++){

			min = G->edge[i][j].minNum, max = G->edge[i][j].maxNum;
			if(!min || !max)
				continue ;
			if(((*v >= min) && (*v <= max)) || ((*v <= min) && (*v >= max))){

				int	newQuan1, newQuan2, newMin1, newMin2, newMax1, newMax2, Xian[2];

				newQuan1 = *v - min + 1, newMin1 = min, newMax1 = *v - 1;
				newQuan2 = max - *v + 1, newMin2 = *v + 1, newMax2 = max;
				Xian[0] = G->edge[i][j].CourseXian[0], Xian[1] = G->edge[i][j].CourseXian[1];
				if(min >= max){

					newQuan1 = min - *v + 1, newMin1 = min, newMax1 = *v + 1;
					newQuan2 = *v - max + 1, newMin2 = *v - 1, newMax2 = max;
				}

				G->edge[i][G->n-1].CourseXian[0] = G->edge[G->n-1][i].CourseXian[0] = Xian[0];
				G->edge[i][G->n-1].CourseXian[1] = G->edge[G->n-1][i].CourseXian[1] = Xian[1];
				G->edge[j][G->n-1].CourseXian[0] = G->edge[G->n-1][j].CourseXian[0] = Xian[0];
				G->edge[j][G->n-1].CourseXian[1] = G->edge[G->n-1][j].CourseXian[1] = Xian[1];
				G->edge[G->n-1][i].quan = G->edge[i][G->n-1].quan = newQuan1;
				if(G->edge[i][G->n-1].quan == 1){

					G->edge[i][G->n-1].maxNum = G->edge[i][G->n-1].minNum = 0;
					G->edge[G->n-1][i].maxNum = G->edge[G->n-1][i].minNum = 0;
				}
				else{

					G->edge[G->n-1][i].maxNum = G->edge[i][G->n-1].minNum = newMin1;
					G->edge[G->n-1][i].minNum = G->edge[i][G->n-1].maxNum = newMax1;
				}

				G->edge[j][G->n-1].quan = G->edge[G->n-1][j].quan = newQuan2;
				if(G->edge[G->n-1][j].quan == 1){

					G->edge[G->n-1][j].maxNum = G->edge[G->n-1][j].minNum = 0;
					G->edge[j][G->n-1].maxNum = G->edge[j][G->n-1].minNum = 0;
				}
				else{

					G->edge[j][G->n-1].maxNum = G->edge[G->n-1][j].minNum = newMin2;
					G->edge[j][G->n-1].minNum = G->edge[G->n-1][j].maxNum = newMax2;
				}

				G->edge[i][j].quan = G->edge[j][i].quan = MAX_NUM;
				G->edge[i][j].minNum = G->edge[i][j].maxNum = 0;
				G->edge[j][i].minNum = G->edge[j][i].maxNum = 0;
				G->vertex[G->n-1].CourseXian[0] = G->edge[i][j].CourseXian[0];
				G->vertex[G->n-1].CourseXian[1] = G->edge[i][j].CourseXian[1];
				if(G->vertex[G->n-1].CourseXian[1])
					G->vertex[G->n-1].CourseXian[2] = -1;
				G->vertex[G->n-1].CourseXian[1] = -1;
				*v = G->n - 1;

				return ;
			}
		}
}

void decide(MGraph *G, int *v0, int *v1)
{
	int	i, j, k, flag0 = 0, flag1 = 0;

	for(i=0; i<G->n; i++)
		if(G->vertex[i].FlatformNum == *v0)
			flag0 = 1;
		else if(G->vertex[i].FlatformNum == *v1)
			flag1 = 1;

	if(flag0 && flag1)	;
	else if(!flag0 && flag1)
		addAPoint(G, v0);
	else if(flag0 && !flag1)
		addAPoint(G, v1);
	else
		addAPoint(G, v0), addAPoint(G, v1);
}
/*
int ReadFile(char *FILE_NAME, char ArcArray[10][50], int *PointPosition)
{
        int     fd, i, j, k;
        char    buf[100], str[100];

        fd = open(FILE_NAME, O_RDONLY);
        read_string :   lseek(fd, *PointPosition, SEEK_SET);
                        if(read(fd, buf, 100) <= 0){

				printf("以读到文件尾 或 读文件出错\n");
                                exit(1);
			}
                        buf[100] = '\0';
                        for(i=0; buf[i]!='#' && buf[i]!='\n'; i++)      ;       //截断得到一行的内容
                        buf[i] = '\0';
                        *PointPosition += strlen(buf) + 1;               //指向被截断的回车后一个字符（下次从这开始）

                        for(i=0; buf[i]=='\t' || buf[i]==32 || buf[i]==','; i++)        ;
        if(!buf[i])
                goto read_string;

        for(i=0, k=0, j=0; buf[i]; i++){

                for(i; buf[i]=='\t' || buf[i]==32 || buf[i]==','; i++)  ;
                if(!buf[i]){

                        close(fd);
                        return k;
                }
                for(j=0, i; buf[i] && (buf[i]!='\t' && buf[i]!=32 && buf[i]!=','); i++)
                        str[j++] = buf[i];
                str[j] = 0, i--;
		strcpy(ArcArray[k++], str);
        }
        close(fd);
        return k;
}
*/
int runRideShort(MGraph *G, int v0, int v1)
{
	MGraph	*GRoute;
	int	i, j, m, n, k=0, w, v, w1, P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int	CourseXian[2][5];
	int	saveShortXian[16][10], d[16], path = 0;
	char	platform[2][30], buf[5];

	GRoute = (MGraph *)malloc(sizeof(MGraph));
	CreateGraph(GRoute, 10);
	
	for(m=0; G->vertex[v0].CourseXian[m]!=0 && G->vertex[v0].CourseXian[m]!=-1; m++)
		CourseXian[0][m] = G->vertex[v0].CourseXian[m];
	for(n=0; G->vertex[v1].CourseXian[n]!=0 && G->vertex[v1].CourseXian[n]!=-1; n++)
		CourseXian[1][n] = G->vertex[v1].CourseXian[n];
	CourseXian[0][m] = CourseXian[1][n] = -1;
	for(i=0; i<16; i++)
		d[i] = -1;

	for(k=0, i=0; i<m; i++)		//起点
		for(j=0; j<n; j++){	//终点

			if(CourseXian[0][i]==-1 || CourseXian[1][j]==-1)
				continue ;
			if((CourseXian[0][i] == CourseXian[1][j])){

				path = G->vertex[CourseXian[0][i]].FlatformNum; d[0] = 0;
//				printf("path = %d", path);
	//			printf("%d\n", CourseXian[0][i]);
				i = m, j = n;	break ;
			}
			ShortTestPath(GRoute, CourseXian[0][i], CourseXian[1][j], P);
			if(flag){	//不通的路径

				flag = 0; break ;
			}
			for(w=0; TruePath[w]!=CourseXian[1][j]; w++)
				saveShortXian[k][w] = TruePath[w];
			saveShortXian[k][w] = TruePath[w];
			saveShortXian[k][w+1] = -1;
			d[k++] = D[CourseXian[1][j]];
		}
	if(!d[0]){

//		printf("*乘坐%d号线可直达*\n", path);
		strcpy(resultInfo2[1], "乘");
		sprintf(buf, "%d", path);
		strcat(resultInfo2[1], buf);
		strcat(resultInfo2[1], "号线直达#");
		strcpy(resultInfo2[0], "-3");
		printf("直达  %s\n", resultInfo2[1]);
		free(G), free(GRoute);
		return 0;
	}
	else
		for(w=10, i=0; i<k; i++)
			if(w > d[i])
				w = d[i];
	resultK = 0;
	for(i=0; i<k; i++)
		if(d[i] == w)
			shortPlatform(G, saveShortXian[i], v0, v1);
	strcpy(resultInfo2[resultK++], "-1");
	
	free(G), free(GRoute);
	return 0;
}
int shortPlatform(MGraph *G, int *pathXian, int v0, int v1)
{
        int	i, j, m, n, v, f0, f1, path[10], k = 0;
	char	platform[40], buf[5];

	path[k++] = G->vertex[v0].FlatformNum, i = 0;
	while(pathXian[i+1] != -1){
	
		m = pathXian[i], n = pathXian[i+1];	//找站点
		for(j=0; j<G->n; j++){

			f0 = f1 = 0;
			for(v=0; G->vertex[j].CourseXian[v] != -1; v++)
				if(G->vertex[j].CourseXian[v] == m)
					f0 = 1;
				else if(G->vertex[j].CourseXian[v] == n)
					f1 = 1;
			if(f0 && f1){
				path[k++] = G->vertex[j].FlatformNum; break ;
			}
		}
		i++;
	}
	path[k] = G->vertex[v1].FlatformNum, path[k+1] = -1;

	for(v=0; v<k; v++){
		
		readPlatformName(&path[v], platform);
		strcpy(resultInfo2[resultK++], platform);
		strcpy(platform, "-(乘");
		sprintf(buf, "%d", pathXian[v]), strcat(platform, buf);
		strcat(platform, "号线)->");
		strcpy(resultInfo2[resultK++], platform);
	}
	readPlatformName(&path[v], platform);
	strcpy(resultInfo2[resultK++], platform);
	strcpy(resultInfo2[resultK++], "-2");
}
int runPathShort(MGraph *G, int v0, int v1)
{
	int	i, k, P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	char	platformName[40];
	
	ShortTestPath(G, v0, v1, P);
	coursePlatform(G, TruePath, v1);
	rideWay(G, TruePath, v1);
}

