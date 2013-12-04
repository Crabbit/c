/* xue sheng lao shi deng ji biao*/
#include<stdio.h>
#define N 2
struct type
{
	char ID[20];
	char name[20];
	char job;
	union
	{
		char grade;
		char work[20];
	}postion;
};
int main()
{
	struct type peo[N];
	void input(struct type peo[]);
	int i=0;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcom to the dengjibiao~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	input(peo);
	printf("ID\t\t\tname\t\t\tjob\t\t\tgrade/work\n");
	for(i=0;i<N;i++)
	{
		if(peo[i].job=='s')
			{
				printf("please input your grade:");
				scanf("%s",&peo[i].postion.grade);
			}
		if(peo[i].job=='t')
			{
				printf("please input your work:");
				scanf("%s",&peo[i].postion.work);
			}
	
		if(peo[i].job=='s')
		printf("%-24s%-24s%-24c%-24s\n",peo[i].ID,peo[i].name,peo[i].job,peo[i].postion.grade);
		if(peo[i].job=='t')
		printf("%-24s%-24s%-24c%-24s\n",peo[i].ID,peo[i].name,peo[i].job,peo[i].postion.work);
	}
	return 0;
}
void input(struct type peo[])
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("please input your ID:");
		scanf("%s",&peo[i].ID);
		printf("please input your name:");
		scanf("%s",&peo[i].name);
		printf("please input your job(Student--s, Teacher--t):");
		scanf("%c",&peo[i].job);
		scanf("%c",&peo[i].job);
	/*	if(peo[i].job=='s')
			{
				printf("please input your grade:");
				scanf("%s",&peo[i].postion.grade);
			}
		if(peo[i].job=='t')
			{
				printf("please input your work:");
				scanf("%s",&peo[i].postion.work);
			}*/
	}
}
