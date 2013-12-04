/* cha xun she sheng cheng ji,bing ji suan bu ji ge ren shu*/
#include<stdio.h>
int main()
{
	int stu[][4]={{60,70,80,90},{56,89,67,88},{34,78,90,66}};
	int (*p)[4];
	int i,n;
	int * search(int (*p)[4],int n);
	int * jisuan(int (*p)[4]);
	printf("~~~~~~~~~What student's score do you wang to see?~~~~~~~~\nplease input the number:");
	scanf("%d",&n);
	p=stu;
	search(stu[][],n);
	jisuan
	
	
}
int * search(int (*p)[4],int n)
{
	int *result;
	result=((*p)+n);
	return (result);
}
