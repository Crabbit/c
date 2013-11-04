#include<stdio.h>


void swap(int *x,int *y)
{
	int r;
	r=*x;
	*x=*y;
	*y=r;
}
int main()
{
	int a=4,b=9;
	printf("a=%d,b=%d\n",a,b);
	swap(&a,&b);
	printf("a=%d,b=%d\n",a,b);
	printf("hahahaha...");
	printf("hahahaha...");
	return 0;
}
