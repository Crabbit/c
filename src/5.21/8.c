#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(struct Student)
struct Student
{
	int number;
	char name[20];
	int score;
	struct Student *next;
};
struct Student * create(void)
{
	struct Student *p1,*p2,*head;
	int n,i;
	p1=p2=(struct Student *)malloc(LEN);
	head=NULL;
	printf("~~~~~~~~~~~~~~~~~~~~~~~Hello~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~How many student do you want to input?~~~~~~\nplease input number:");
		scanf("%d",&n);
	printf("~~~~~~~Please input student's information~~~~~~~~\n");
	for(i=1;p1!=NULL;i++)
	{
		printf("Please input your number:");
		scanf("%d",&p1->number);
		printf("Please input your name  :");
		scanf("%s",p1->name);
		printf("Please input your score :");
		scanf("%d",&p1->score);
		if(i==1)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
		p1=(struct Student *)malloc(LEN);
		if(i==n)
			p1=NULL;
	}
	return (head);
}
void output(struct Student *h)
{
	printf("NO.\t\tname\t\tscore\n");
	for(;h!=NULL;)
	{
		printf("%d%19s%19d\n",h->number,h->name,h->score);
		h=h->next;
	}
}
void delete(struct Student *a,struct Student *b)
{
	struct Student *ha,*hb,*t;
	ha=a;
	hb=b;
	a=a->next;
	
	for(;ha->next!=NULL;)
	{
		for(;hb!=NULL;)
		{
			if(a->number==hb->number)
			{
				t=ha->next=a->next;
				a=a->next;
			}
			hb=hb->next;
		}
		hb=b;
		a=a->next;
		ha=ha->next;
	}
}
int main()
{
	struct Student *a,*b;
	a=create();
	printf("This is A :\n");
	output(a);
	b=create();
	printf("This is B :\n");
	output(b);
	delete(a,b);
	printf("This is delted A:\n");
	output(a);
	return 0;
}
