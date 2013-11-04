#include<stdio.h>
#define M 3
#define N 2
void fun(char a[],int j,int k)
{
	int n;
	for(n=0;n<M+N;n++)
		a[n]='A';
	a[j]='B';
	a[k]='B';
	for(n=0;n<N+M;n++)
	{
		printf("%c",a[n]);
	}
	printf("\n");
}
int main()
{
	int i,j,k=0;
	char a[M+N];
	for(i=0;i<M+N;i++)
	{	
		k=i+1;
		for(j=i;k<M+N;k++)
		{
			fun(a,j,k);
		}
	}
	return 0;
}
