#include<stdio.h>
#define N 3
int main()
{
	int a[N];
	int *p;
	int i,j,k,r;
	for(i=0;i<N;i++)
	{
		printf("please input the %d number:",i+1);
		scanf("%d",&a[i]);
	}
	p=a;
	printf("The str is:\n");
	for(i=0;i<N;i++)
	{
		printf("%d\t",*(p+i));
	}
	printf("\n");
	for(i=0;i<N;i++)
	{
		k=i;
		for(j=i;j<N;j++)
		{
			if(*(p+k)>*(p+j))
				k=j;
		}
			r=*(p+i);
			*(p+i)=*(p+k);
			*(p+k)=r;
	}
	printf("Ths swap str is:\n");
	for(i=0;i<N;i++)
	{
		printf("%d\t",*(p+i));
	}
	printf("\n");
	return 0;
}
