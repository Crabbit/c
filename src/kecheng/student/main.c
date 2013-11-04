#include<stdio.h>
#include<stdlib.h>

#include "input.c"

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
int main()
{
	struct Student *h;
	int sum[3]={0};
	float ave[3]={0};
	h=input();
	caculate(sum,ave,h);
	return 0;
}
