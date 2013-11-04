#include<stdio.h>
#define M 5
#define N 6
int main()
{
	int l[M][N];
	int r[M][N];
	int i,j,n,t=0,a=0,b=0,c=0,d=0;
	int *p;
	p=l;
	for(i=0;i<M;i++)
	for(j=0;j<N;j++)
	{
		printf("Please input the number:");
		scanf("%d",&l[i][j]);
	}
	printf("You input the str is:\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%d\t",l[i][j]);
		}
		printf("\n");
	}
	for(n=1;a+c<M&&b+d<N;n++)
	{
		if(n%4==1)
			{
				for(i=a;i<N-a;i++,t++)
				{
					r[a][i]=*(p+t);
				}
				a++;
			}
		if(n%4==2)
			{
				for(i=b+1;i<M-b;i++,t++)
				{
					r[i][N-b-1]=*(p+t);
				}
				b++;
			}
		if(n%4==3)
			{
				for(i=N-c-2;i>c-1;i--,t++)
				{
					r[M-1-c][i]=*(p+t);
				}
				c++;
			}
		if(n%4==0)
			{
				for(i=M-d-2;i>d;i--,t++)
				{
					r[i][d]=*(p+t);
				}
				d++;
			}
	}
	printf("Luo xuan hua zhi hou:\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%d\t",r[i][j]);
		}
		printf("\n");
	}
	return 0;
}
