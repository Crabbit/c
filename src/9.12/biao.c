#include<stdio.h>
#include<string.h>

struct function
{
	int xishu;
	char unknow;
	int zhishu;
	char nextc;
	struct function *last;
	struct function *next;
}

struct function * create_fun()
{
	struct function *head;
	struct function *h1,*h2;
	printf( "~~Welcome to the lili's Function-caculate~~\n" );
	printf( "Please input the function:" );
	head = h1 = (struct function )malloc(sizeof function);
	for( ;h1->nextc == ''; )
	{
		h2 = (struct function)malloc(sizeof function);
		h1->next = h2;
		h2 = h1;
	}
}

void Print(struct function *h)
{
	for(;h != NULL;)
	{
		printf( "%d%c^%d %c ";h->xishu,h->unknow, );
	}
}

int main()
{
	
}
