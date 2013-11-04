#include<stdio.h>
struct A1
{
	short a;
	double b;
	char c;
};
struct A2
{
	char a;
	short b;
	double c;
};
int main()
{
	struct A1 A;	
	struct A2 B;
	int a,b;
	a=sizeof (A);
	b=sizeof (B);
	printf("A zhan yong %d\n",a);
	printf("B zhan yong %d\n",b);
	return 0;
}
