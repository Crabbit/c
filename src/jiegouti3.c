/*        ji suan ri qi         */
#include<stdio.h>
struct date
{
	int year;
	int month;
	int day;
}
jisuan(struct date ji)
{
	int i,d=0;
	int nd[13]={31,28,31,30,31,30,31,31,30,31,30,31};
	int yd[13]={31,29,31,30,31,30,31,31,30,31,30,31};
	printf("Please input the date(year):");
	scanf("%d",&ji.year);
	printf("Please input the date(month):");
	scanf("%d",&ji.month);
	printf("Please input the date(day):");
	scanf("%d",&ji.day);
	printf("Date is :%d  %d  %d\n",ji.year,ji.month,ji.day);
	if(ji.year%100==0&&ji.year%400==0||ji.year%100!=0&&ji.year%4==0)
		{
			for(i=0;i<ji.month-1;i++)
				d=d+yd[i];
			d=d+ji.day;
			printf("The date is %d day int the year.\n",d);
		}
	else
		{
			for(i=0;i<ji.month-1;i++)
				d=d+nd[i];
			d=d+ji.day;
			printf("The date is %d day int the year.\n",d);
		}
}
int main()
{
	struct date ji;
	jisuan(ji);
	return 0;
}
