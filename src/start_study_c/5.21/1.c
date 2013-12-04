#include<stdio.h>
#define N 10
struct student
{
	int num;
	char name[20];
	int score;
};
void Number(struct student stu[])
{
	struct student r;
	struct student *p=stu,*q;
	int i,j;
	for(i=0;i<N-1;i++)
	{
		q=p=&stu[i];
		for(j=i+1;j<N;j++)
		{	
			if(p->num>stu[j].num)
				p=&stu[j];
		}
		r=*q;
		*q=*p;
		*p=r;
	}
	p=&stu[0];
	printf("An zhao Number pai xu:\nNo.\t\tname\t\tscore\t\t\n");
	for(i=0;i<N;i++,p++)
	{
		printf("%d%16s%16d\n",p->num,p->name,p->score);
	}
	
}
void Name(struct student stu[])
{
	struct student r;
	struct student *p=stu,*q;
	int i,j;
	for(i=0;i<N-1;i++)
	{
		q=p=&stu[i];
		for(j=i+1;j<N;j++)
		{
			if(strcmp(p->name,stu[j].name)>0)
				p=&stu[j];
		}
		r=*q;
		*q=*p;
		*p=r;
	}
	p=&stu[0];
	printf("An zhao Name pai xu:\nNo.\t\tname\t\tscore\t\t\n");
	for(i=0;i<N;i++,p++)
	{
		printf("%d%16s%16d\n",p->num,p->name,p->score);
	}
}
void Score(struct student stu[])
{
	struct student r;
	struct student *p=stu,*q;
	int i,j;
	for(i=0;i<N-1;i++)
	{
		q=p=&stu[i];
		for(j=i+1;j<N;j++)
		{
			if(p->score>stu[j].score)
				p=&stu[j];
		}
		r=*q;
		*q=*p;
		*p=r;
	}
	p=&stu[0];
	printf("An zhao Score pai xu:\nNo.\t\tname\t\tscore\t\t\n");
	for(i=0;i<N;i++,p++)
	{
		printf("%d%16s%16d\n",p->num,p->name,p->score);
	}
}
int main()
{
	struct student stu[N];
	char c;
	int i;
	for(i=0;i<N;i++)
	{
		printf("please input your number:");
		scanf("%d",&stu[i].num);
		printf("please input your name:");
		scanf("%s",&stu[i].name);
		printf("please input your score:");
		scanf("%d",&stu[i].score);
	}
	Number(stu);
	Name(stu);
	Score(stu);
	return 0;
}
