/*
 *Copyright (c) lili.
 *All rights reserved.
 *
 *File			:	Bolld_Suger_main.c
 *Time			:	2013.5.3
 *Editor		:	lili
 *Email			:	lili00681@gamil.com
 *Thanks		:	google
 *
 * This is the program of Blood sugar simulation.
 * For homework.
 * */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<error.h>
#include<time.h>

float Get_blood_sugar_content();
int   Get_the_battery( void );

int main()
{
	float 	Sick_Weight;

	char	Sick_Choice;

	float 	Sick_Start_blood_sugar;
	float 	Sick_Real_blood_sugar;
	float	Sick_add_blood_sugar;

	time_t 	now_time;
	struct tm *timeinfo;

	int	battery;

	printf( "~~~~~~~~~~~~~~~~~~~~~~~~~Welcom~~~~~~~~~~~~~~~~~~~~~~~\n" );
	printf( "****/This is a blood sugar simultaion.\n" );
	printf( "****/Did you want to power on the machine?( y / n )\t" );
	scanf( "%c",&Sick_Choice );
	if( Sick_Choice == 'Y' || Sick_Choice == 'y')
	{
		printf( "****/Initialize your persional information.\n****/\n****/\n" );
		printf( "****/Please input your weight:" );
		scanf( "%f",&Sick_Weight );

		Sick_Start_blood_sugar = ( float )Sick_Weight * 0.22;

		battery = Get_the_battery();
		while( 1 )
		{
			battery = battery - 3;

			if( battery <= 30 )
				printf( "\nThe Battery is too low\n" );
			else
				printf( "The battery is %d  .\n",battery );

			time ( &now_time );
			timeinfo = localtime( &now_time );
			printf( "Time is : %s\n\n\n\n",asctime( timeinfo ) );
			
			printf( "****/Detection your blood sugar content?( y / n )\t" );
			while (getchar() != '\n');
			scanf( "%c",&Sick_Choice );

			if( Sick_Choice == 'Y' || Sick_Choice == 'y')
				Sick_Real_blood_sugar = Get_blood_sugar_content();
			
			if ( Sick_Real_blood_sugar > 110 )
			{
				printf( "****/\n****/Did you want to add insulin?( y / n )\t" );
				while (getchar() != '\n');
				scanf( "%c",&Sick_Choice );
				if( Sick_Choice == 'Y' || Sick_Choice == 'y')
				{
					Sick_add_blood_sugar = ( Sick_Real_blood_sugar - Sick_Start_blood_sugar) / 15;
					printf( "****/Your sugar is too high\n" );
					printf( "****/You should add %f Insulin\n",Sick_add_blood_sugar );
				}
			}
		}
	}
	return 0;
}

float Get_blood_sugar_content( void )
{
	int 	Real_blood_sugar;

			srand( time ( NULL ) );
			Real_blood_sugar = rand()%( 130 - 10 ) + 10;
			printf( "****/Your sugar content is %d mg/dl.\n****/\n",Real_blood_sugar );

			if( 80 < Real_blood_sugar && Real_blood_sugar < 110 )
				printf( "****/Your sugar content is normal.\n" );
			else
			{
				if( Real_blood_sugar < 80 )
					printf( "****/Your sugar is too low,you should supplmentary some sugar.\n" );
				else
					printf( "****/Your sugar is too high\n" );
			}

//			printf( "****/You should add %f \n****/\n",add_blood_sugar );
	return Real_blood_sugar;
}

int Get_the_battery( void )
{
	int 	Battery;
		srand( time ( NULL ) );
		Battery = rand()%( 100 - 1 ) + 1;
	
	return Battery;
}
