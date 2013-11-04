#include<stdio.h>
int main()
{
	enum Color { red, orange, yellow, green, blue, black, white};
	enum Color i,j,k,pri;
	int n = 0,loop = 0;
	for( i = red ; i <= white ; i++ )
	{	
		for( j = red ; j <= white ; j++ )
		{
			if( i != j )
				for ( k = red ; k <= white ; k++ )
				{
					if( k != j && k!= i)
					{
						n++;
						printf("%d",n);
						for( loop=1; loop <= 3; loop++)
						{
							switch( loop )
							{
								case 1: pri=i; break;
								case 2: pri=j; break;
								case 3: pri=k; break;
								default : break;
							}
							switch ( pri )
							{
								case red: printf("\t\tred");break;
								case orange: printf("\t\torange");break;
								case yellow: printf("\t\tyellow");break;
								case green: printf("\t\tgreen");break;
								case blue: printf("\t\tblue");break;
								case black: printf("\t\tblack");break;
								case white: printf("\t\twhite");break;
								default : break;
							}
						}
						printf("\n");
					}
				}
		}
	}
	printf("Total is :%d",n);
	return 0;
}
