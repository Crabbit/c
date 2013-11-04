#include<stdio.h>
int print();
int a=10;
void main(void)
{
	int a=0;
	a = print();
	printf("%d",a);
}
int print()
{
	int a=5;
	printf("%d\n",a++);
	return a;
}
