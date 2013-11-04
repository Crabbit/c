#include<stdio.h>
#define N 4
int main()
{
	int a[N];
	int *p;
	int i,j,r;
	for(i=0;i<N;i++)
	{
		printf("Please input the number that not ZERO!:");
		scanf("%d",&a[i]);
	}
	for(i=0;i<N;i++)
	{
		if(a[i]>0)
		{
			for(j=i;j<N;j++)
			{	
				if(a[N-j-1]<0)
				{	
					r=a[N-j-1];
					a[N-j-1]=a[i];
					a[i]=r;
				}
			}
		}
		
	}
	printf("The swap str is:\n");
	for(i=0;i<N;i++)
		printf("%d\t",a[i]);
	printf("\n");
	return 0;
}
