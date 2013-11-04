//此程序通过指针将字符串反向
#include<stdio.h>
#define N 10
int main()
{
	int str[N]={1,2,3,4,5,6,7,8,9,10};
	int *p=str;
	printf("The str is :");
	for( i=0; i < N ; i++ )
		printf("%d  ",*(p+i));
	printf("\n");
	for( i = 0; i < N;i++ )
	{
	}
	printf("The swap str is :");
	for( i=0; i < N ; i++ )
		printf("%d  ",*(p+i));
	printf("\n");
	return 0;
}
