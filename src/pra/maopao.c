#include<stdio.h>
#define N 20
int main()
{
	int str[N]={5,9,78,96,34,63,22,47,81,99,73,11,36,79,33,24,62,69,37,40};
	int i, j, r;
	for ( i=0 ; i < 20 ; i++ )
		for( j=0 ; j<N-i ; j++ )
		{
			if( str[j-1] > str[j] )
			{
				r = str[j-1];
				str[j-1] = str[j];
				str[j] = r;
			}
		}
	printf(" this is the result:\n");
	for ( i=0 ; i < N ; i++ )
		printf("%d  " , str[i] );
	printf("\n");
	return 0;
}
