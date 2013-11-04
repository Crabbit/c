#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define LEN sizeof( struct TEL_NUM )

struct TEL_NUM
{
	char	phone_num[16];
	struct TEL_NUM	*next; 
};

struct EFF_NUM
{
	int	phone_num;
	int		count;
	struct	EFF_NUM	*next; 
};

int map[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0};

struct TEL_NUM *Create_ORI( int NUM )
{
//point
	struct TEL_NUM *p1,*p2,*h;
//count
	int		i;

	p1 = p2 = (struct TEL_NUM *)malloc( LEN );
	for( i = 1; i <= NUM; i++ )
	{
		printf( "Please input the string number:\n" );
		scanf( "%s", &p1->phone_num );
		if( i == 1 )
			h = p2;
		else
			p2->next = p1;
		p2 = p1;
		if( i == NUM )
		{
			p2->next = NULL;
		}
		p1 = ( struct TEL_NUM *)malloc( LEN ); 
	}
	return h;
}

int main( )
{
//telphone total quantity
	int NUM;
//count
	int i;
//telphone effect number
	int EFFECT_num = 0;
//Effective phone number
	struct EFF_NUM *EFF_head, *EFF_now, *EFF_now_l, *EFF_new;
//origin number
	struct TEL_NUM *ORI_Head, *ORI_Next;
//swap origin phone number
	char	swap_num_ori[16];
//swap effective phone number
	int	num_eff_single = 0;
	int	num_eff_sum = 0;
//flag - map
	int	MAP_flag = 0;
//real int mod
	int	mod;
	
	printf( "please input the count:\n" );
	scanf( "%d",&NUM );

	ORI_Head = ORI_Next = Create_ORI( NUM );
	EFF_head = EFF_now = ( struct EFF_NUM *)malloc( LEN );
	EFF_now->count = 0;
	EFF_now->next = NULL;
	
	for( ORI_Next = ORI_Head; ORI_Next != NULL; ORI_Next = ORI_Next->next )
	{
		strcpy( swap_num_ori,ORI_Next->phone_num );
//translate to xxx-xxxx num(int xxxxxxx).
		for( i = 0, EFFECT_num = 0, num_eff_sum = 0; EFFECT_num < 7; i++  )
		{
			if( swap_num_ori[i] >= 48 && swap_num_ori[i] <= 57 )
			{
				EFFECT_num++;
				num_eff_single = swap_num_ori[i] - 48;
				num_eff_sum = num_eff_sum + num_eff_single * pow( 10, 7 - EFFECT_num );
				
			}
			if( swap_num_ori[i] >= 65 && swap_num_ori[i] <= 89)
			{
				EFFECT_num++;
				MAP_flag = swap_num_ori[i] - 'A';
				num_eff_single = map[MAP_flag];
				num_eff_sum = num_eff_sum + num_eff_single * pow( 10, 7 - EFFECT_num );
			}
		}
//insert to the suit location
		printf( "The first number is %d\n",num_eff_sum );
// 1st phone number
		if( ORI_Next == ORI_Head )
		{
			EFF_now->count = 1;
			EFF_now->phone_num = num_eff_sum;
			EFF_now->next = NULL;
		}
		else
 			for( EFF_now = EFF_head; 1 ; EFF_now = EFF_now->next )
 			{
				EFF_now_l = EFF_now->next;
// 2nd is smaller than 1st
				if( num_eff_sum < EFF_head->phone_num )
				{
					EFF_new = (struct EFF_NUM *)malloc( LEN );
					EFF_new->phone_num = num_eff_sum;
					EFF_new->count = 1;
					EFF_new->next = EFF_head;
					EFF_head = EFF_new;
					break;
				}
// 2nd is lager than 1st
				else
				{
					if( num_eff_sum == EFF_now->phone_num )
					{
						EFF_now->count += 1;
						break;
					}
					if( EFF_now_l == NULL && num_eff_sum > EFF_now->phone_num )
					{
						EFF_new = (struct EFF_NUM *)malloc( LEN );
						EFF_new->phone_num = num_eff_sum;
						EFF_new->count = 1;
						EFF_new->next = NULL;
						EFF_now->next = EFF_new;
						break;
					}
// EFF_now is not the last phone number and the effective number is more than his next 
					if( EFF_now_l != NULL && num_eff_sum < EFF_now_l->phone_num )
					{
						EFF_new = (struct EFF_NUM *)malloc( LEN );
						EFF_new->phone_num = num_eff_sum;
						EFF_new->count = 1;
						EFF_new->next = EFF_now_l;
						EFF_now->next = EFF_new;
						break;
					}
				}

			}
	}

	for( EFF_now = EFF_head; EFF_now != NULL ; EFF_now = EFF_now->next  )
	{
		if( EFF_now->count != 1 )
		{
			mod = EFF_now->phone_num % 10000;
			printf( "%d-", (EFF_now->phone_num - mod) / 10000);
			printf( "%d %d\n", mod, EFF_now->count );
		}
	}
	return 0;
}
