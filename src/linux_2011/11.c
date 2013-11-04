#include<stdio.h>
int fun3(int x)
{
	static int a=3;
	a+=x;
	return a;
}
int main()
{
	int k=2,m=1,n;
	n=fun3(k);
	n=fun3(m);
	printf("n=%d\n",n);
	return 0;
}
