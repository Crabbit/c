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
	p=a;
	for(i=0;i<N;i++)
	{
		if(*(p+i)>0)
		{
			for(j=i;j<N;j++)
			{	
				if(*(p+N-j-1)<0)
				{	
					r=*(p+N-j-1);
					*(p+N-j-1)=*(p+i);
					*(p+i)=r;
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
