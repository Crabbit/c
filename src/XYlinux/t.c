#include<stdio.h>
int main()
{
	char *p1,*p3;
	char **p2, ***p4;
	char i='c';
	p3 = &i;
	p2 = &p3;
	p1 = &p2;
	p4 = p1;
	printf(" %hjk,hkj,");
	return 0;
}
