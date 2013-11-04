#include<stdio.h>
#include<string.h>
int main()
{
	char str[100];
	char del[20];
	int del_substr(char *str,char *substr);
	printf("Please input the str:");
	scanf("%s",&str);
	printf("Please input the del str:");
	scanf("%s",&del);
	del_substr(str,del);
	return 0;
}
int del_substr(char *str,char *substr)
{
	int l,i,j,k;
	char stra[100],strb[100],strg[20]={0};
	l=strlen(substr);
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]==substr[0])
		{
			k=i;
			for(j=0;j<l;j++,k++)
			{
				strg[j]=str[k];
			}
			if(strcmp(strg,substr)==0)
			{
				k=0;
				if(str[i+l]!='\0')
				{
					for(j=i+l;str[j]!='\0';j++,k++)
					{
						strb[k]=str[j];
					}
					strcat(stra,strb);
				}
				break;
			}
		}
		stra[i]=str[i];
	}
	stra[i+l+k]='\0';
	printf("The new str is:");
	printf("%s\n",stra);
	return 0;
}
