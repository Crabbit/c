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
	struct Student *head;
	struct Student *p1,*p2;
	int n,i;
	p1=p2=(struct Student *)malloc(LEN);
	head=NULL;
	printf("How many student's infomation do you want to input?\nplease input the number:");
		scanf("%d",&n);
	printf("~~~~Please Input some student infomation~~~~\n");
	for(i=1;p1!=NULL;i++)
	{
		printf("Please Input your NO.  :");
		scanf("%d",&p1->number);
		printf("Please Input your name :");
		scanf("%s",p1->name);
		printf("Pleaee Input your score:");
		scanf("%d",&p1->score);
		if(i==1)
			head=p1;
		else 
			p2->next=p1;
		p2=p1;
		p1=(struct Student * )malloc(LEN);
		if(i==n)
			p1=NULL;
	}
	return (head);
}
void queren(struct Student *head)
{
	printf("This is the all student's infomation,who do you want to delete?\n");
	printf("NO.\t\tname\t\tscoer\n");
	for(;head!=NULL;)
	{
		printf("%d%19s%19d\n",head->number,head->name,head->score);
		head=head->next;
	}
}
void input(struct Student *head)
{
	printf("This is the grade you delete.\n");
	for(;head!=NULL;)
	{
		printf("%d%19s%19d\n",head->number,head->name,head->score);
		head=head->next;
	}
}
void delete(struct Student *head)
{
	int del;
	struct Student *p;
	p=head;
	p=p->next;
	printf("Please Input the number that your want to delete:");
	scanf("%d",&del);
	if(head->number==del)
		head=head->next;
	for(;head->next!=NULL;)
	{
		if(p->number==del)
			{
				head->next=p->next;
				break;
			}
		head=head->next;
		p=p->next;
	}
}
int main()
{
	struct Student *h;
	h=create();
	queren(h);
	delete(h);
	input(h);
	return 0;
}
