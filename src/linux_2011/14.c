#include<stdio.h>
void tran(char *m,char **n)
{
	*n=m;
}
int main()
{
	char a[15] = "XiYouLinux";
	char *b;
	tran(a,&b);
	printf("b:%s\n",b);
	return 0;
}
