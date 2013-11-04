#include<stdio.h>
int main()
{
	int n = 1;
	int str[10]={ 34, 78, 23, 11, 56, 77, 39, 11, 72, 85};
	int th[10];
	int i,j;
	for( i=0; i < 10; i++ )
	{
		for( j=0; j < 10; j++ )
		{
			if( str[i] > str[j] )
				n++;
		}
		th[i]=n;
		n=1;
	}
	printf("The str is :\n");
	for( i = 0; i < 10; i++ )
		printf("%d  ",str[i]);
	printf("\nThe sort in is :\n");
	for( i = 0; i < 10; i++ )
		printf("%d   ",th[i]);
	printf("\n");
	return 0;
}
