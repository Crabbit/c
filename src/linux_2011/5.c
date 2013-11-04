#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	int n=0;
	char *p="1010110110";
	int i;
	for(i=0;i<strlen(p);i++)
	{
		n=n+(p[i]-48)*pow(2,strlen(p)-i-1);
	}
	printf("%d\n",n);
	return 0;
}
