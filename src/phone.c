/* input the num and the name */
#include<stdio.h>
#define N 3
struct user 
{
	char name[20];
	char num[10];
};
void input(struct user s[])
{
	int i;
	for(i=0;i<N;i++)
		{
			printf("please input the name:");
			scanf("%s",s[i].name);
			printf("please input the number:");
			scanf("%s",s[i].num);
		}
}
void paixu(struct user s[])
{
	struct user r;
	int i,j,k;
	for(i=0;i<N-1;i++)
		{	k=i;
			for(j=i+1;j<N;j++)
				if(strcmp(s[k].name,s[j].name)>0)
					k=j;
				r=s[k];
				s[k]=s[i];
				s[i]=r;
		}
}
void output(struct user s[])
{
	int i;
	printf("Name	num\n");
	for(i=0;i<N;i++)
	printf("%s\t%s\n",s[i].name,s[i].num);
}
int main()
{
	struct user s[3];
	void input(struct user s[]);
	void paixu(struct user s[]);
	void output(struct user s[]);
	input(s);
	paixu(s);
	output(s);
	return 0;
	
}
