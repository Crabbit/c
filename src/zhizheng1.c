#include<stdio.h>
#define N 3
void swap(int * p)
{
	int r,i,j,k;
	for(i=0;i<N;i++)
	{
		k=i;
		for(j=i;j<N;j++)
		{
			if(*(p+k)>*(p+j))
				k=j;
			r=*(p+i);
			*(p+i)=*(p+k);
			*(p+k)=r;
		}
	}
	printf("the swap str is :");
	for(i=0;i<N;i++)
	{
		printf("%d\t",*(p+i));
	}
	printf("\n");
		
}
int main()
{
	int a[N];
	int i,*p;
	void swap(int *t);
	for(i=0;i<N;i++)
		{
			printf("Please input the %d number:",i);
			scanf("%d",&a[i]);
		}
	*p=a;
	swap(p);
	return 0;
}
