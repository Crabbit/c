#include<stdio.h>
enum {blue,red};
int main()
{
	int i=1;
	do{
		printf("%d\n",i);
		i++;
		if(i<15)
		continue;
	}while(blue);
	return 0;
}
