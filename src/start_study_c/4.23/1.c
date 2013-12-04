#include<stdio.h>
int y(int x,int y)
{
	int i,a;
	for(i=1;i<=x&&i<=y;i++)
		if(x%i==0&&y%i==0)	a=i;
	return a;
}
int main()
{
	int a,b,c,d;
	int y(int x,int y);
	printf("please input two number:");
	scanf("%d%d",&a,&b);
	c=y(a,b);
	d=a/c*b;
	printf("%d and %d gongyueshu=%d\n",a,b,c);
	printf("%d and %d gongbeishu=%d\n",a,b,d);
	return 0;
}
