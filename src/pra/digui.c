#include<stdio.h>
int Digui( int m,int n )
{
	int z;
	if( n==0 || m==n )
		z=1;
	if( n==1 )
		z=m;
	if( m!=n && n!=1 && n!=0 )
		{
			z=Digui(m-1,n-1);
			z=z+Digui(m-1,n);
		}
	return (z);
}
int main()
{
	int m,n;
	int z;
	printf( "Please input the M and N:" );
	scanf("%d %d",&m,&n);
	z=Digui(m,n);
	printf( "\nThe  result  is  :%d \n",z );
	return 0;
}
