#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN sizeof(struct Student)
struct Student
{
	int num;
	char name[20];
	int MT;
	int EN;
	int PH;
	float ave;
	int sum;
	struct Student *next;
};


struct Student *input(void)
{
	struct Student *head,*p1,*p2;
	int i,n;
	p1=p2=(struct Student *)malloc(LEN);
	head=NULL;
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~Welcom to the student manage system~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~How many student do you want to input?~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~Please input the number :");
		scanf("%d",&n);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~Please input student information~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for(i=1;p1!=NULL;i++)
	{
		printf("Please input your Number   :");
			scanf("%d",&p1->num);
		printf("Please input your name	   :");
			scanf("%s",&p1->name);
		printf("Please input your MT score :");
			scanf("%d",&p1->MT);
		printf("Please input your EN score :");
			scanf("%d",&p1->EN);
		printf("Pleaee input your PH score :");
			scanf("%d",&p1->PH);
		if(i==1)
			head=p2;
		else
			p2->next=p1;
		p2=p1;
		p1=(struct Student *)malloc(LEN);
		if(i==n)
			p1=NULL;
	}
	return (head);
}


void caculate(int sum[],float ave[],struct Student *h)
{
	for(;h!=NULL;)
	{
		h->sum=h->MT+h->EN+h->PH;
		h->ave=h->sum/3.0;
		sum[0]=sum[0]+h->MT;
		sum[1]=sum[1]+h->EN;
		sum[2]=sum[2]+h->PH;
		h=h->next;
	}
}


void output(struct Student *h)
{
        printf("NO.\t\tname\t\tMTscore\t\tENscore\t\tPHscore\t\tSum\t\tAve\n");
        for(;h!=NULL;)
        {
                printf("%d%19s%20d%16d%13d%13d%13f\n",h->num,h->name,h->MT,h->EN,h->PH,h->sum,h->ave);
                h=h->next;
        }
}



void paixu(struct Student *h)
{
        char s;
	struct Student *nexth,*head,*r,*k;
	head=h;
	printf("~~~~~~~~~~~Do you want to sort it according to the students ID?~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~If you want,please input Y~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		getchar();
		scanf("%c",&s);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~This is the information you input~~~~~~~~~~~~~~~~~~~~~\n");
        if(s=='Y'||s=='y')
	{
		for(;head!=NULL;)
        	{
			k=head;
			for(nexth=head->next;nexth!=NULL;nexth=nexth->next)
			{
				if(k->num>nexth->num)
					k=nexth;
			}
			r->num=k->num;strcpy(r->name,k->name);r->MT=k->MT;r->EN=k->EN;r->PH=k->PH;r->sum=k->sum;r->ave=k->ave;
			k->num=head->num;strcpy(k->name,head->name);k->MT=head->MT;k->EN=head->EN;k->PH=head->PH;k->sum=head->sum;k->ave=head->ave;
			head->num=r->num;strcpy(head->name,r->name);head->MT=r->MT;head->EN=r->EN;head->PH=r->PH;head->sum=r->sum;head->ave=r->ave;
			head=head->next;
        	}
		output(h);
	}

        printf("\n~~~~~~~~~~~~~~~~~~~what way do you want to use to sort in?~~~~~~~~~~~~~~~~~~~\n");
        printf("Please input your chorice (A :max->min,B min->max):");
		getchar();
                scanf("%c",&s);
        if(s=='B'||s=='b')
        {
       		 for(;head!=NULL;)
       		{
			k=head;
			for(nexth=head->next;nexth!=NULL;nexth=nexth->next)
			{
				if(k->sum<nexth->sum)
					k=nexth;
			}
			r->num=k->num;strcpy(r->name,k->name);r->MT=k->MT;r->EN=k->EN;r->PH=k->PH;r->sum=k->sum;r->ave=k->ave;
			k->num=head->num;strcpy(k->name,head->name);k->MT=head->MT;k->EN=head->EN;k->PH=head->PH;k->sum=head->sum;k->ave=head->ave;
			head->num=r->num;strcpy(head->name,r->name);head->MT=r->MT;head->EN=r->EN;head->PH=r->PH;head->sum=r->sum;head->ave=r->ave;
			head=head->next;
        	}
		output(h);
        }
        if(s=='B'||s=='b')
        {
       		 for(;head!=NULL;)
       		{
			k=head;
			for(nexth=head->next;nexth!=NULL;nexth=nexth->next)
			{
				if(k->sum>nexth->sum)
					k=nexth;
			}
			r->num=k->num;strcpy(r->name,k->name);r->MT=k->MT;r->EN=k->EN;r->PH=k->PH;r->sum=k->sum;r->ave=k->ave;
			k->num=head->num;strcpy(k->name,head->name);k->MT=head->MT;k->EN=head->EN;k->PH=head->PH;k->sum=head->sum;k->ave=head->ave;
			head->num=r->num;strcpy(head->name,r->name);head->MT=r->MT;head->EN=r->EN;head->PH=r->PH;head->sum=r->sum;head->ave=r->ave;
			head=head->next;
        	}
		output(h);
        }
}



int main()
{
	struct Student *h;
	int sum[3]={0};
	float ave[3]={0};
	h=input();
	caculate(sum,ave,h);
	output(h);
	paixu(h);
	return 0;
}

