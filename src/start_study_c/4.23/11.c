#include<stdio.h>
static char r[10];
void del(char s[],char c)
{
	int i,n=0;
	for(i=0;i<10;i++)
	if(s[i]!=c){r[n]=s[i];n++;}
	
}
int main()
{
	char s[10];
	char c;
	printf("please input the char:");	
	gets(s);
	printf("please input the char you want to del:");	
	scanf("%c",&c);
	del(s,c);
	puts(r);
	return 0;

}
