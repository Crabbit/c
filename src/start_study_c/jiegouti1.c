/*jie gou ti    xue sheng guan li xi tong */
#include<stdio.h>
#define N 2
struct Student
{
	char number[20];
	char name[20];
	int score[3];
	float save;
};
int main()
{
	struct Student stu[N];
	struct Student maxstu;
	
	int i;
	float maxave;
	
	void input(struct Student stu[]);
	void average(struct Student stu[]);
	float max(struct Student stu[]);
	
	input(stu);
	average(stu);

	printf("Name\t\t\tNO.\t\t\tscore1\t\t\tscore2\t\t\tscore3\t\t\taverage\n");
	for(i=0;i<N;i++)
		printf("%-24s%-24s%-24d%-24d%-24d%-24f\n",stu[i].name,stu[i].number,stu[i].score[0],stu[i].score[1],stu[i].score[2],stu[i].save);

	maxave=max(stu);

 	
	for(i=0;i<N;i++)
		if(maxave==stu[i].save)
			maxstu=stu[i];
	printf("\nThe max average's student is:%s",maxstu.name);
	printf("His info:\n");
	printf("%-24s%-24s%-24d%-24d%-24d%-24f\n",maxstu.name,maxstu.number,maxstu.score[0],maxstu.score[1],maxstu.score[2],maxstu.save);
	return 0;
}
void input(struct Student stu[])
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("please input the student's name:");
		scanf("%s",stu[i].name);
		printf("please input the NO:");
		scanf("%s",stu[i].number);
		printf("please input your score1:");
		scanf("%d",&stu[i].score[0]);
		printf("please input your score2:");
		scanf("%d",&stu[i].score[1]);
		printf("please input your score3:");
		scanf("%d",&stu[i].score[2]);
	}
}	
void average(struct Student stu[])
{
	int i,j;
	for(i=0;i<N;i++)
	{
		stu[i].save=0;
		for(j=0;j<3;j++)
			stu[i].save+=stu[i].score[j];
		stu[i].save=stu[i].save/3.0;
	}
}
float max(struct Student stu[])
{
	int i;
	float max=stu[0].save;
	for(i=1;i<N;i++)
	{	
		if (max<stu[i].save)
			max=stu[i].save;
	}
	return max;
}





