#include<stdio.h>
void Createuser(void)
{
	FILE *pass=fopen("Passwd","a");
	char pd[20],rpd[20],na[20];
	printf("\nPlease input your Name, and then,press enter to confirm :");
		scanf("%s",na);
	while(1)
	{
		printf("\nPlease input your Password,and then,press enter to confirm:");
		scanf("%s",pd);
		printf("\nPlease enter your password again to confirm,and then,press enter to confirm:");
		scanf("%s",rpd);
		if(strcmp(pd,rpd)==0)
		{
			printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Congratulations to you ^_^, the user is Successfully Created~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			fwrite(na,20,1,pass);
			fwrite(pd,20,1,pass);
			break;
		}
		printf("\nSorry ::>_<::,you enter the password are not the same,please re-input\n");
	}
	fclose(pass);
}
void Configpasswd(void)
{
	FILE *pass;
	pass=fopen("Passwd","rb+");
	char pd[20],na[20],inpd[20],inna[20];
	char s;
	int i=1,n=1,cishu=1;
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tips~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nIf you are a malicious attempt, the program will automatically shut down.\n\n");
	while(1)
	{
		if(cishu==6)
		{
			printf("\n\nDetected malicious attempt,   the program will be shut down.\n\n");
			goto end;
		}
		cishu++;
		printf("\nPlease input your name:");
			scanf("%s",inna);
		while(1)
		{
			fread(na,20,1,pass);
			if(strcmp(na,inna)==0)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcome %s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n",na);
				i=1;
				while(1)
				{
					printf("Please input your password:");
					scanf("%s",inpd);
					while(1)
					{
						fread(pd,20,1,pass);
						if(strcmp(pd,inpd)==0)
						{
							printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Login is Successful~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcom Back~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");s
							goto end;
						}
						else
						{
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry,Login Failed >_<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							if(i==3)
							{
								printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry ,you try to much >.<~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
								goto end;
							}
							printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~You have three opportunities to try~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("\n~~~~~~~~~~~~~~~~Press 'E' to exit this system ,Press any key to login again~~~~~~~~~~~~~~\n");
							printf("Please make your chice:");
								getchar();
								scanf("%c",&s);
							if(s=='E')
								goto end;
							i++;
							break;
						}
						
					}
					
				}
				break;
			}
			if(fgetc(pass)==-1)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry,You enter the user doesn't exist~~~~~~~~~~~~~~~~~~~~\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~Please input your name again~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				n=1;
				fclose(pass);
				pass=fopen("Passwd","rb+");
				break;
			}
			fclose(pass);
			pass=fopen("Passwd","rb+");
			fseek(pass,n*40L,1);
			n++;
		}
	}
	end :fclose(pass);
}
int main()
{
	char s;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Are you a member?~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~If NOt,come on,Press 'j' to join us~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~or if you are,Press 'l' to log on~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~If you are not interested in,Press 'E' to exit this program~~~~~~~~\n");
	printf("Make your choice:");
		scanf("%c",&s);
	printf("%c\n",s);
	if(s=='j')
		Createuser();
	if(s=='l')
		Configpasswd();
	if(s=='E')
	return 0;
}
