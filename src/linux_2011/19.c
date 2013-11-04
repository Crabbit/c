#include<stdio.h>
#define N 12
int main()
{
	int f1=1,f2=1;
	int i;
	printf("Fibonacci:\n%d\t%d\t",f1,f2);
	for(i=3;i<=N;i++)
		{
			f1=f1+f2;
			f2=f1+f2;
			printf("%d\t",f1);
			printf("%d\t",f2);
		}
	printf("\n");
	return 0;
}
