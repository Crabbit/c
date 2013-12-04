#include<stdio.h>
static int m;
static int n;
static int f;
static int g;
int max(int x,int y)
{
	int z;
	return(z=(x>y?x:y));
}
int min(int x,int y)
{
	int z;
	return(z=(x>y?y:x));
}
int mxstr(int str[4][4])
{
	int max(int x,int y);
	int a,b,maxn=str[0][0];
	m=1,n=1;
	for(a=0;a<4;a++)
		for(b=0;b<3;b++)
			{
				maxn=max(str[a][b+1],maxn);
				if(maxn==str[a][b+1]) {m=a+1;n=b+2;}
			}
	return maxn;
				
}
int mnstr(int str[4][4])
{
	int min(int x,int y);
	int a,b,minn=str[0][0];
	f=1,g=1;
	for(a=0;a<4;a++)
		for(b=0;b<3;b++)
			{
				minn=min(minn,str[a][b+1]);
				if(minn==str[a][b+1]) {f=a+1;g=b+2;}
			}
	return minn;
}
int main()
{
	int max(int x,int y);
	int max(int x,int y);
	int str[4][4];
	int i,j;
	int maxn,minn;
	printf("please input the str:");
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			{
				scanf("%d",&str[i][j]);
			}
	printf("your str is:\n");
	for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			printf("%d\t",str[i][j]);
			printf("\n");
		}
	maxn=mxstr(str);
	minn=mnstr(str);
	printf("The str's max number is%d\n",maxn);
	printf("And the maxn is %dhang %d lie\n",m,n);
	printf("The str's min number is%d\n",minn);
	printf("And the minn is %dhang %d lie\n",f,g);
	return 0;
}
