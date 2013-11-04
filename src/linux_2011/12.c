#include<stdio.h>
#include<string.h>
int del_substr(char *str,char *substr)
{
	char strg[100];
	int i,j,l,n=0,m,k;
	l=strlen(substr);
	for(i=0,m=0;str[i]!='\0';i++,m++)
	{
		if(str[i]==substr[0])
		{
			k=i;
			for(j=0;j<l;j++,k++)
			{
				if(str[k]==substr[j])
					n++;
			}
		}
		if(n!=l)
			n=0;
		if(n==l)
			{
				i=i+l;
				n=0;
			}
		strg[m]=str[i];
	}
	strg[m]='\0';
	printf("The new str is:\n");
	printf("%s",strg);
	printf("\n");
	return 0;
}
int main()
{
	char str[100],del[20];
	printf("Please input the str:");
	scanf("%s",&str);
	printf("Please input the delte str:");
	scanf("%s",&del);
	del_substr(str,del);
	return 0;
}

