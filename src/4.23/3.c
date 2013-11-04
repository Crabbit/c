#define N 10
#include<stdio.h>
int peo(int a[])
{
	int i,g=0,m=0;
	float ave;
	for(i=0;i<N;i++)
		{
			g=g+a[i];
		}
	ave=g*1.0/N;
	printf("The average is %f\n",ave);
	for(i=0;i<N;i++)
		if(a[i]>ave) m++;
	return m;
}
int main()
{
	int peo(int a[]);
 	int a[N];
	int p,i;
	for(i=0;i<N;i++)
		{
			printf("please input the grade:");
			scanf("%d",&a[i]);
			if(a[i]<0) break;
		}
	p=peo(a);
	printf("There is %d student behind the average.\n",p);
	return 0;
}
