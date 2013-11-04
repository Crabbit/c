/* 
 *  Student Manager system.
 *
 *  File 			: 	mainNICE.c
 *  Editer 			: 	李力
 *  Class number 		: 	04113123
 *  Time 			: 	2012.05.05
 *  Version 			: 	1.0
 *
 *
 *
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<curses.h>

#define LEN sizeof(struct Student)

struct Student
{
	int num;
	char name[20];
	int MT;
	int EN;
	int PH;
	int C;
	float ave;
	int sum;
	int pai;
	char garde;
	char jiguan[30];
	struct Student *next;
};



void Createuser(void)   /* 创建用户函数*/
{
	FILE *pass;
	char pd[20],rpd[20],na[20];
	pass=fopen("Passwd","w");
	fclose(pass);					/*  这两段用于新建一个passwd的文件 */
	pass=fopen("Passwd","a");
	printf("\nPlease input your Name, and then,press enter to confirm :");
		scanf("%s",na);
	while(1)
	{
		printf("\nPlease input your Password,and then,press enter to confirm:");
		system("stty -echo");			/*	系统调用，让密码不回显		*/
		scanf("%s",pd);
		system("stty echo");			/*	系统调用，让输入之后开始显示	*/
		printf("\nPlease enter your password again to confirm,and then,press enter to confirm:");
		system("stty -echo");			/*	系统调用，让密码不回显		*/
		scanf("%s",rpd);
		system("stty echo");			/*	系统调用，让输入之后开始显示	*/
		if(strcmp(pd,rpd)==0)
		{
			printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Congratulations to you ^_^, the user is Successfully Created~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			fwrite(na,20,1,pass);
			fwrite(pd,20,1,pass);                 /*   一旦创建成功，则把用户名和密码存进去   */
			break;
		}
		printf("\nSorry ::>_<::,you enter the password are not the same,please re-input\n");
	}
	fclose(pass);
}



int  Configpasswd(void)                          /*   验证普通用户与密码的函数   */
{
	FILE *pass;
	char pd[20],na[20],inpd[20],inna[20];
	char s;
	int i=1,n=1,cishu=1,z=0;
	pass=fopen("Passwd","rb+");
	printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tips~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("If you are a malicious attempt, the program will automatically shut down!!!!\n\n");
	while(1)
	{
		if(cishu==6)
		{
			printf("\n\nDetected malicious attempt,   the program will be shut down.\n\n");
			goto end;
		}
		cishu++;			/*  	一旦恶意登录超过5次，则跳出程序		*/
		printf("\nPlease input your name:");
			scanf("%s",inna);
		while(1)
		{
			fread(na,20,1,pass);
			if(strcmp(na,inna)==0)		/*	用来匹配用户名，如果输入的用户名和文件中的相同，则执行花括号内		*/
			{
				printf("\n\n\n\n\n\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcome %s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n\n\n\n\n\n",na);
				i=1;
				while(1)
				{
					printf("Please input your password:");
					system("stty -echo");			/*	系统调用，让密码不回显		*/
					scanf("%s",inpd);
					system("stty echo");			/*	系统调用，让输入之后开始显示	*/
					while(1)
					{
						fread(pd,20,1,pass);		/*	用来匹配密码，如果相同，则登录成功	*/
						if(strcmp(pd,inpd)==0)
						{
							printf("\n\n\n\n\n\n");
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Login is Successful~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcom Back ^_^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
							z=1;
							goto end;
						}
						else				/*	否则，显示输入失败，重新输入或者退出程序	*/
						{
							printf("\n\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry,Login Failed >_<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							if(i==3)
							{
								printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry ,you try to much >.<~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
								goto end;
							}
							printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~You have three opportunities to try~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("\n~~~~~~~~~~~~~~~~Press 'E' to exit this system ,Press any key to login again~~~~~~~~~~~~~~\n\n\n\n\n");
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
			if(fgetc(pass)==-1)			/*	读取用户名是从文件中一个一个读取，如果读取到最后都没发现用户，则提示用户不存在	*/
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
	return (z);
}

int  ConfigAdmin(void)					/* 	验证管理员密码，原理与验证普通用户基本一直	*/
{
	FILE *pass;
	char pd[20],na[20],inpd[20],inna[20];
	char s;
	int i=1,n=1,cishu=1,z=0,m=0;
	pass=fopen("Admin","rb+");
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
				printf("\n\n\n\n\n\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcome %s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n\n\n\n\n\n",na);
				i=1;
				while(1)
				{
					printf("Please input your password:");
					system("stty -echo");
					scanf("%s",&inpd);
					system("stty echo");
					while(1)
					{
						fread(pd,20,1,pass);
						if(strcmp(pd,inpd)==0)
						{
							printf("\n\n\n\n\n\n");
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Login is Successful~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Welcom Back ^_^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n");
							z=1;
							goto end;
						}
						else
						{
							printf("\n\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry,Login Failed >_<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
							if(i==3)
							{
								printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Sorry ,you try to much >.<~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
								goto end;
							}
							printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~You have three opportunities to try~~~~~~~~~~~~~~~~~~~~~~~\n");
							printf("\n~~~~~~~~~~~~~~~~Press 'E' to exit this system ,Press any key to login again~~~~~~~~~~~~~~\n\n\n\n\n");
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
	return (z);
}



struct Student *input(void)			/* 	学生成绩的输入，用到了链表	*/	
{
	struct Student *ReadFile(struct Student *h);
	struct Student *head,*p1,*p2,*h1,*h2,*h;
	int i,n,j;
	char *file="stu_dat";
	FILE *f;
	f=fopen("stu_dat","a+");		/*	以追加的方式打开文件，将每次输入的内容追加到原来数据前面	*/
	p1=p2=(struct Student *)malloc(LEN);
	h1=h2=ReadFile(h1);
	head=h=NULL;
	printf("\n\n~~~~~~~How many student do you want to input?~~~~~~\n\n\n\n");
	printf("~~~~~~~~Please input the number :");
		scanf("%d",&n);
	printf("\n\n\n\n~~~~~~~~~Please input student information~~~~~~~~~\n\n\n\n\n");
	for(i=1;p1!=NULL;i++)
	{
		if(i!=1)
		{
			printf("~~~~~~~~~~~~~     Please    input    the    next    student's    information.    ~~~~~~~~~~~\n");
			h1=h2;
			h=head;
		}
		P:printf("Please    input    your    Student    ID  :");	
			scanf("%d",&p1->num);
			h1=h2;
			h=head;
		if(h1->num!=p1->num)			/*	用来保证学号的唯一性，每次输入完学号之后都进行一次检测	*/
		{
			for(;h1!=NULL;)			/*	分两种情况考虑，这是输入的成绩与原来存在的数据进行比较	*/
			{
				if(h1->num==p1->num)
				{
					printf("Sorry,Please   check   your   ID,the  ID  you  inputed  is  alerady  exits.\n\n");
					goto P;
				}
				h1=h1->next;
			}
			for(j=1;j<i;j++)		/*	这是第二种情况，这次输入中的学好和刚刚输入的学号进行比较	*/
			{
				if(h->num==p1->num)
				{
					printf("Sorry,Please   check   your   ID,the  ID  you  inputed  is  alerady  exits.\n\n");
					goto P;
				}
				h=h->next;
			}
		}
		else
		{
			printf("Sorry,Please   check   your   ID,the  ID  you  inputed  is  alerady  exits.\n\n");
			goto P;
		}
		printf("Please     input     your     name	  :");
			scanf("%s",&p1->name);
		printf("Please   input   your   Math   score      :");
			scanf("%d",&p1->MT);
		printf("Please   input   your   English   score   :");
			scanf("%d",&p1->EN);
		printf("Pleaee   input   your   Physics   score   :");
			scanf("%d",&p1->PH);
		printf("Pleaee   input   your  C program  score   :");
			scanf("%d",&p1->C);
		printf("Please     input     your     Home town   :");
			scanf("%s",&p1->jiguan);
		fwrite(p1,LEN,1,f);		/*	当输入完毕时，存入文件		*/
		if(i==1)
			head=h=p2;
		else
			p2->next=p1;
		p2=p1;
		if(i==n)
			{
				p2->next=NULL;
				break;
			}
		p1=(struct Student *)malloc(LEN);
	}
	fclose(f);
	return (head);
}



struct Student *ReadFile(struct Student *h)			/*	此函数是个辅助函数，用来读取学生数据文件，并返回头指针	*/
{
        struct Student *p1,*p2,*p3;				/* 	原理与录入学生成绩差不多，只不过从文件读取数据罢了	*/
        FILE *Read;
	int i=0;
        Read=fopen("stu_dat","r+");				/*	以只读的方式打开文件	*/
        h=p1=p2=p3=(struct Student *)malloc(LEN);
	for(;fread(p2,LEN,1,Read)!='\0';i++)
        {
                p1=(struct Student *)malloc(LEN);		/*	创建新节点，把读取的数据存入每个链表中	*/
                p2->next=p1;
                p2=p1;
        }
	if(i!=0)
	{
	while(p3->next!=p2)
        	p3=p3->next;
	p3->next=NULL;
	}
	if(i==0)
	{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                                                           Error!!!	The  Date  doesn't  exist  !!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}
        return (h);
}




struct Student *caculate(int sum[],float ave[],struct Student *h)	/*	计算学生成绩的函数，保存在学生ave与sum这两个变量中	*/
{
	struct Student *a;
	int i;
	a=h;
	for(i=0;i<5;i++)
	{
		sum[i]=0;
		ave[i]=0;
	}
	for(i=0;h!=NULL;i++)
	{
		h->sum=h->MT+h->EN+h->PH+h->C;
		h->ave=h->sum/4.0;
		sum[0]=sum[0]+h->MT;
		sum[1]=sum[1]+h->EN;
		sum[2]=sum[2]+h->PH;
		sum[3]=sum[3]+h->C;
		h=h->next;
	}
		sum[4]=sum[0]+sum[1]+sum[2]+sum[3];
		ave[0]=sum[0]*1.0/i;
		ave[1]=sum[1]*1.0/i;
		ave[2]=sum[2]*1.0/i;
		ave[3]=sum[3]*1.0/i;
		ave[4]=sum[4]*1.0/i;
	return(a);
}




void output(struct Student *h)				/*	纯输出函数，行参是个头指针	*/
{
        printf("NO.\t\tname\t\tMath score\tEnglish score\t\tPhysics score\t\tC program score\t\tSum\t\tAve\t\t\tHomeTow\n\n");
        for(;h!=NULL;)
        {
                printf("%d%19s%19d%20d%20d%20d%23d%23f%20s\n",h->num,h->name,h->MT,h->EN,h->PH,h->C,h->sum,h->ave,h->jiguan);
                h=h->next;
        }
}




void paixu(struct Student **h)				/*	排序函数，用来对学生成绩进行排序	*/
{
	char s;
	struct Student *nexth,*lasth1,*lasth2,*head,*r;
	int i=0;
	head=lasth1=lasth2=*h;
	printf("\n*************************************   What way do you want to use to sort in?   **************************************\n*\n***\n*****\n*******\n");
	printf("*-*-*-*-            A           :                     Math           score.		\n*\n");
	printf("*-*-*-*-            B           :                   English          score.		\n*\n");
	printf("*-*-*-*-            C           :     	            Physics          score.		\n*\n");
	printf("*-*-*-*-            D           :      	           C  Program        score.		\n*\n");
	printf("*-*-*-*-            E           :		     Students           ID              \n*\n");
	printf("*-*-*-*-            F           :		     Students          name             \n*\n*\n*\n");
	printf("*-*-*-*-            Q           :     Exit   to   the   Main  Select  Director     :>_<:\n*******\n*****\n***\n*\n");	
	printf("**************************************************************************************************************************\n\n\n\n\n");
	printf("~~~~Hey~~~Hey~~~~~~~~~Make   your   choice   ~^-^~  :");
		getchar();
                scanf("%c",&s);
	while(head!=NULL)
	{
		if(s=='A'||s=='a')		head->pai=head->MT;		/* 单独用pai这个数据来存取将要进行排序的数据，之后就只需要排列pai这个数据就行了	*/
		if(s=='B'||s=='b')		head->pai=head->EN;
		if(s=='C'||s=='c')		head->pai=head->PH;
		if(s=='D'||s=='d')		head->pai=head->C;
		if(s=='E'||s=='e')		head->pai=head->num;
		if(s=='Q'||s=='q')		goto PaixuEnd;
		head=head->next;
	}
	head=*h;
	if(s=='f'||s=='F')
	{
		printf("**************************   What  the  way  you  want  to  use  to  sort  in  ?   *************************\n*\n***\n*****\n");
		printf("*-*-*-		    A		:	Max           ->             Min                  \n*\n*\n*\n*\n");
		printf("*-*-*-		    B		:	Min           ->             Max                  \n*****\n***\n*\n");
		printf("************************************************************************************************************\n\n\n\n");
		printf("~~~~Hey~~~Hey~~~Hey~~~~~~Make   your   choice   ~^-^~  :");
			getchar();
			scanf("%c",&s);
		if(s=='a'||s=='A')
		{
			for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
		 	{
				for(nexth=head->next;nexth!=NULL;)
				{
					if(head==*h&&strcmp(head->name,nexth->name)<0)				//如果是第一个，并且第一个于第二个，则单独进行指向的改变
					{
						if(lasth2==*h)					
						{
							head->next=nexth->next;				//看是不是相邻的交换，因为两种交换方式不一样
							nexth->next=head;				//将head的指向改为指向较小的后面那个
							r=head;
							head=*h=nexth;
							nexth=r;					//用r做中间量，交换head和nexth的名字所对应的地址
							lasth2=*h;					//在相邻情况下，使lasth的指向初始为头部地址
							nexth=nexth->next;
							lasth2=lasth2->next;				//由于下面式子的影响，单独控制他们的下移
						}
						else
						{	
							lasth2->next=nexth->next;
							nexth->next=head;
							head=*h=nexth;
							nexth=lasth2;
							nexth=nexth->next;				//只让nexth下移，不让lasth2下移，使lasth2在nexth前面
						}
					}
					else 
					{
							nexth=nexth->next;
							lasth2=lasth2->next;				//由于可能第一个比较小，所以无法判别，所以要保证式子的下移
					}
				}
				head=head->next;							//在head在两个循环中都通过这个语句使head下移
				if(nexth==NULL)
					{
						lasth2=head;
						nexth=head->next;
					}
			}
		
		        for(;head!=NULL;)
			{
				for( nexth=head->next;nexth!=NULL;)					//上面循环已经将最小的放头部了，所以这个循环用来排序即可
				{
					if(i==0)							//此语句在循环中只执行一次，用来在这个循环中初始化head，lasth1和lasth2的值	
					{
						head=lasth1=lasth2=*h;
						nexth=(*h)->next;
						i++;
					}
					if(head!=(*h)&&strcmp(head->name,nexth->name)<0)				//不是第一个的，作为另外一种情况考虑
					{
						lasth2->next=nexth->next;
						lasth1->next=nexth;
						nexth->next=head;
						r=head;
						head=nexth;
						nexth=r;
						
					}
					lasth2=nexth;							//用来保证lasth2永远在nexth前面
					nexth=nexth->next;						//使nexth下移
				}
				lasth1=head;								//用来保证lasth1永远在head前面
				head=lasth2=head->next;							//使head下移
		        }
			output(*h);
			goto PaixuEnd;
		}
		if(s=='b'||s=='B')
		{
			for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
		 	{
				for(nexth=head->next;nexth!=NULL;)
				{
					if(head==*h&&strcmp(head->name,nexth->name)>0)				//如果是第一个，并且第一个于第二个，则单独进行指向的改变
					{
						if(lasth2==*h)					
						{
							head->next=nexth->next;				//看是不是相邻的交换，因为两种交换方式不一样
							nexth->next=head;				//将head的指向改为指向较小的后面那个
							r=head;
							head=*h=nexth;
							nexth=r;					//用r做中间量，交换head和nexth的名字所对应的地址
							lasth2=*h;					//在相邻情况下，使lasth的指向初始为头部地址
							nexth=nexth->next;
							lasth2=lasth2->next;				//由于下面式子的影响，单独控制他们的下移
						}
						else
						{	
							lasth2->next=nexth->next;
							nexth->next=head;
							head=*h=nexth;
							nexth=lasth2;
							nexth=nexth->next;				//只让nexth下移，不让lasth2下移，使lasth2在nexth前面
						}
					}
					else 
					{
							nexth=nexth->next;
							lasth2=lasth2->next;				//由于可能第一个比较小，所以无法判别，所以要保证式子的下移
					}
				}
				head=head->next;							//在head在两个循环中都通过这个语句使head下移
				if(nexth==NULL)
					{
						lasth2=head;
						nexth=head->next;
					}
			}
		
		        for(;head!=NULL;)
			{
				for( nexth=head->next;nexth!=NULL;)					//上面循环已经将最小的放头部了，所以这个循环用来排序即可
				{
					if(i==0)							//此语句在循环中只执行一次，用来在这个循环中初始化head，lasth1和lasth2的值	
					{
						head=lasth1=lasth2=*h;
						nexth=(*h)->next;
						i++;
					}
					if(head!=(*h)&&strcmp(head->name,nexth->name)>0)				//不是第一个的，作为另外一种情况考虑
					{
						lasth2->next=nexth->next;
						lasth1->next=nexth;
						nexth->next=head;
						r=head;
						head=nexth;
						nexth=r;
						
					}
					lasth2=nexth;							//用来保证lasth2永远在nexth前面
					nexth=nexth->next;						//使nexth下移
				}
				lasth1=head;								//用来保证lasth1永远在head前面
				head=lasth2=head->next;							//使head下移
		        }
			output(*h);
			goto PaixuEnd;
		}
	}
	printf("**************************   What  the  way  you  want  to  use  to  sort  in  ?   *************************\n*\n***\n*****\n");
	printf("*-*-*-		    A		:	Max           ->             Min                  \n*\n*\n*\n*\n");
	printf("*-*-*-		    B		:	Min           ->             Max                  \n*****\n***\n*\n");
	printf("************************************************************************************************************\n\n\n\n");
	printf("~~~~Hey~~~Hey~~~Hey~~~~~~Make   your   choice   ~^-^~  :");
		getchar();
		scanf("%c",&s);
	printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   This is the sort students information   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	if(s=='A'||s=='a')										//从大到小排序
	{
		for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
	 	{
			for(nexth=head->next;nexth!=NULL;)
			{
				if(head==*h&&head->pai<nexth->pai)				//如果是第一个，并且第一个于第二个，则单独进行指向的改变
				{
					if(lasth2==*h)					
					{
						head->next=nexth->next;				//看是不是相邻的交换，因为两种交换方式不一样
						nexth->next=head;				//将head的指向改为指向较小的后面那个
						r=head;
						head=*h=nexth;
						nexth=r;					//用r做中间量，交换head和nexth的名字所对应的地址
						lasth2=*h;					//在相邻情况下，使lasth的指向初始为头部地址
						nexth=nexth->next;
						lasth2=lasth2->next;				//由于下面式子的影响，单独控制他们的下移
					}
					else
					{	
						lasth2->next=nexth->next;
						nexth->next=head;
						head=*h=nexth;
						nexth=lasth2;
						nexth=nexth->next;				//只让nexth下移，不让lasth2下移，使lasth2在nexth前面
					}
				}
				else 
				{
						nexth=nexth->next;
						lasth2=lasth2->next;				//由于可能第一个比较小，所以无法判别，所以要保证式子的下移
				}
			}
			head=head->next;							//在head在两个循环中都通过这个语句使head下移
			if(nexth==NULL)
				{
					lasth2=head;
					nexth=head->next;
				}
		}
	
	        for(;head!=NULL;)
		{
			for( nexth=head->next;nexth!=NULL;)					//上面循环已经将最小的放头部了，所以这个循环用来排序即可
			{
				if(i==0)							//此语句在循环中只执行一次，用来在这个循环中初始化head，lasth1和lasth2的值
				{
					head=lasth1=lasth2=*h;
					nexth=(*h)->next;
					i++;
				}
				if(head!=(*h)&&head->pai<nexth->pai)				//不是第一个的，作为另外一种情况考虑
				{
					lasth2->next=nexth->next;
					lasth1->next=nexth;
					nexth->next=head;
					r=head;
					head=nexth;
					nexth=r;
					
				}
				lasth2=nexth;							//用来保证lasth2永远在nexth前面
				nexth=nexth->next;						//使nexth下移
			}
			lasth1=head;								//用来保证lasth1永远在head前面
			head=lasth2=head->next;							//使head下移
	        }
		output(*h);
		goto PaixuEnd;
	}
	if(s=='B'||s=='b')										//从大到小排序
	{
		for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
	 	{
			for(nexth=head->next;nexth!=NULL;)
			{
				if(head==*h&&head->pai>nexth->pai)				//如果是第一个，并且第一个大于第二个，则单独进行指向的改变
				{
					if(lasth2==*h)					
					{
						head->next=nexth->next;				//看是不是相邻的交换，因为两种交换方式不一样
						nexth->next=head;				//将head的指向改为指向较小的后面那个
						r=head;
						head=*h=nexth;
						nexth=r;					//用r做中间量，交换head和nexth的名字所对应的地址
						lasth2=*h;					//在相邻情况下，使lasth的指向初始为头部地址
						nexth=nexth->next;
						lasth2=lasth2->next;				//由于下面式子的影响，单独控制他们的下移
					}
					else
					{	
						lasth2->next=nexth->next;
						nexth->next=head;
						head=*h=nexth;
						nexth=lasth2;
						nexth=nexth->next;				//只让nexth下移，不让lasth2下移，使lasth2在nexth前面
					}
				}
				else 
				{
						nexth=nexth->next;
						lasth2=lasth2->next;				//由于可能第一个比较小，所以无法判别，所以要保证式子的下移
				}
			}
			head=head->next;							//在head在两个循环中都通过这个语句使head下移
			if(nexth==NULL)
				{
					lasth2=head;
					nexth=head->next;
				}
		}
	
	        for(;head!=NULL;)
		{
			for( nexth=head->next;nexth!=NULL;)					//上面循环已经将最小的放头部了，所以这个循环用来排序即可
			{
				if(i==0)							//此语句在循环中只执行一次，用来在这个循环中初始化head，lasth1和lasth2的值
				{
					head=lasth1=lasth2=*h;
					nexth=(*h)->next;
					i++;
				}
				if(head!=(*h)&&head->pai>nexth->pai)				//不是第一个的，作为另外一种情况考虑
				{
					lasth2->next=nexth->next;
					lasth1->next=nexth;
					nexth->next=head;
					r=head;
					head=nexth;
					nexth=r;
					
				}
				lasth2=nexth;							//用来保证lasth2永远在nexth前面
				nexth=nexth->next;						//使nexth下移
			}
			lasth1=head;								//用来保证lasth1永远在head前面
			head=lasth2=head->next;							//使head下移
	        }
		output(*h);
		goto PaixuEnd;
	}
	PaixuEnd:printf("\n\n*********************************************************************************************************************\n\n");
}

void Change(void)			/*	改变学生信息的函数，最后会存入文件中	*/
{
		struct Student *h;
		FILE *change;
		int n;
		char s;
		change=fopen("stu_dat","r");
		h=ReadFile(h);
		fclose(change);
		output(h);
		printf("\nThis is the all student's information,What do you want to change?\n\n");
		while(1)
		{
			printf("Please input the Student ID you want to change:");
				scanf("%d",&n);
			printf("\n\n\nDo you want to modify the information of the NO.%d Student?\n\n\n",n);
			printf("\n\n\nPlease press 'Y' to confim it,Or press AnyKey to input again.\n\n\n");
				getchar();
				scanf("%c",&s);
			if(s=='Y'||s=='y')
			{
				change=fopen("stu_dat","w+");
				while(h!=NULL)
				{
					if(h->num==n)
					{
						printf("This is the %d student's information,Please input the new information.\n\n",n);
       						printf("NO.\t\tname\t\tMath score\tEnglish score\t\tPhysics score\t\tC program score\t\tSum\t\tAve\t\t\tHomeTow\n\n");
                				printf("%d%19s%19d%20d%20d%20d%23d%23f%20s\n",h->num,h->name,h->MT,h->EN,h->PH,h->C,h->sum,h->ave,h->jiguan);
							printf("Please     input     your     Number      :");
								scanf("%d",&h->num);
							printf("Please     input     your     name	  :");
								scanf("%s",&h->name);
							printf("Please   input   your   Math   score      :");
								scanf("%d",&h->MT);
							printf("Please   input   your   English   score   :");
								scanf("%d",&h->EN);
							printf("Pleaee   input   your   Physics   score   :");
								scanf("%d",&h->PH);
							printf("Pleaee   input   your  C program  score   :");
								scanf("%d",&h->C);
							printf("Please     input     your     Home town   :");
								scanf("%s",&h->jiguan);
					}
					fwrite(h,LEN,1,change);		/* 录入完新数据后，存盘	*/
					h=h->next;
				}
				printf("\n\n\n\nChange Success~~~~^-^~~~~\n\n\n\n\n");
				break;
			}
		}
	fclose(change);
}



void Find(struct Student *h)		/*	查找学生信息函数	*/
{
	char s;
	char name[20];
	int n;
	printf("\n\n\n\n\n\n\n~~~~~~~~~~~~~~~~~~~~     What   the   way   you   want   to  use   to  Find   the   Student   information  ~~~~~~~~~~~~~\n|\n|\n");
	printf("|*-*-*-*-            A           :                  Student's	        	name					\n|\n|\n");
	printf("|*-*-*-*-            B           :                  Student's	        	 ID					\n|\n|\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n\n");
	printf("~~~   Hey   Hey  ^-^~~~  Make  your  choice  :");
		getchar();
		scanf("%c",&s);
	if(s=='a'||s=='A')
	{
		printf("\n\n   Please   input   the   Student   Name   you  want   to   know  :");
		scanf("%s",&name);
		while(h!=NULL)
		{
			if(strcmp(name,h->name)==0)	/*	检测是否使输入的名字	*/
			{
				printf("\n\n\n~~~~~~~~   This   is   the   student's   information:\n\n");
        			printf("NO.\t\tname\t\tMath score\tEnglish score\t\tPhysics score\t\tC program score\t\tSum\t\tAve\t\t\tHomeTow\n\n");
                		printf("%d%19s%19d%20d%20d%20d%23d%23f%20s\n",h->num,h->name,h->MT,h->EN,h->PH,h->C,h->sum,h->ave,h->jiguan);
			}
			h=h->next;
		}
	}
	if(s=='b'||s=='B')
	{
		printf("\n\n   Please   input   the   Student   ID   you  want   to   know  :\n\n");
		scanf("%d",&n);
		while(h!=NULL)
		{
			if(n==h->num)			/*	检测是否是输入的学号	*/
			{
				printf("\n\n\n~~~~~~~~   This   is   the   student's   information:");
        			printf("NO.\t\tname\t\tMath score\tEnglish score\t\tPhysics score\t\tC program score\t\tSum\t\tAve\t\t\tHomeTow\n\n");
                		printf("%d%19s%19d%20d%20d%20d%23d%23f%20s\n",h->num,h->name,h->MT,h->EN,h->PH,h->C,h->sum,h->ave,h->jiguan);
				
			}
			h=h->next;
		}
	}
}


void List(struct Student *h)				/*	列出学生成绩函数	*/
{
	int i=0,j=0,n[5]={0},v=0;
	char s;
	char o='%';
	int max,min;
	struct Student *head;
	head=h;
	printf("\n********************************   What  Subjuts  result  do  you  want  to  see  ?   **********************************\n*\n***\n*****\n*******\n");
	printf("*-*-*-*-            A           :                         Math           		\n*\n");
	printf("*-*-*-*-            B           :                        English         		\n*\n");
	printf("*-*-*-*-            C           :     	                 Physics          		\n*\n");
	printf("*-*-*-*-            D           :      	                C  Program              	\n*\n");
	printf("*-*-*-*-            E           :		          Ave                           \n*\n*\n*\n*\n");
	printf("*-*-*-*-            Q           :     Exit   to   the   Main  Select  Director     :>_<:\n*******\n*****\n***\n*\n");	
	printf("**************************************************************************************************************************\n\n\n\n\n");
	printf("~~~~Hey~~~Hey~~~~~~~~~Make   your   choice   ~^-^~  :");
		getchar();
		scanf("%c",&s);
	while(head!=NULL)
	{ 
		if(s=='A'||s=='a')		
		{
			head->pai=head->MT;
			if(head==h)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    This  is  the  Math  result   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
				printf("	  Level	:	Score     Segment");
				printf("                                                    Percentage                                         Number  rate\n\n");
			}
		}
		if(s=='B'||s=='b')
		{
			head->pai=head->EN;
			if(head==h)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   This  is  the  English  result   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				printf("	  Level	:	Score     Segment");
				printf("                                                    Percentage                                         Number  rate\n\n");
			}
		}
		if(s=='C'||s=='c')
		{
			head->pai=head->PH;
			if(head==h)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   This  is  the  Physics  result   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				printf("	  Level	:	Score     Segment");
				printf("                                                    Percentage                                         Number  rate\n\n");
			}
		}
		if(s=='D'||s=='d')
		{
			head->pai=head->C;
			if(head==h)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   This  is  the  C Program  result   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				printf("	  Level	:	Score     Segment");
				printf("                                                    Percentage                                         Number  rate\n\n");
			}
		}
		if(s=='E'||s=='e')
		{
			head->pai=head->ave;
			if(head==h)
			{
				printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   This  is  the  Ave  result   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				printf("	  Level	:	Score     Segment");
				printf("                                                    Percentage                                         Number  rate\n\n");
			}
		}
		if(s=='Q'||s=='q')		goto ListEnd;
		head=head->next;
	}
	head=h;
	for(i=0;head!=NULL;i++)
	{
		if(head->pai>=90) n[0]++;
		if(head->pai>=80&&head->pai<90) n[1]++;
		if(head->pai>=70&&head->pai<80) n[2]++;
		if(head->pai>=60&&head->pai<70) n[3]++;
		if(head->pai<60) n[4]++;
		head=head->next;
	}
		printf("*-*-*-	   A	:	90    ->    100   [");
		for(v=0;v<100*(n[0]*1.0/i);v++)
		printf("*");
		for(v=0;v<100-100*(n[0]*1.0/i);v++)
		printf("-");
		printf("]   %d  %c%f\n",n[0],o,100*n[0]*1.0/i);
		printf("*-*-*-	   B	:	80    ->    90    [");
		for(v=0;v<100*(n[1]*1.0/i);v++)
		printf("*");
		for(v=0;v<100-100*(n[1]*1.0/i);v++)
		printf("-");
		printf("]   %d  %c%f\n",n[1],o,100*n[1]*1.0/i);
		printf("*-*-*-	   C	:	70    ->    80    [");
		for(v=0;v<100*(n[2]*1.0/i);v++)
		printf("*");
		for(v=0;v<100-100*(n[2]*1.0/i);v++)
		printf("-");
		printf("]   %d  %c%f\n",n[2],o,100*n[2]*1.0/i);
		printf("*-*-*-	   D	:	60    ->    70    [");
		for(v=0;v<100*(n[3]*1.0/i);v++)
		printf("*");
		for(v=0;v<100-100*(n[3]*1.0/i);v++)
		printf("-");
		printf("]   %d  %c%f\n",n[3],o,100*n[3]*1.0/i);
		printf("*-*-*-	   E	:            <  60        [");
		for(v=0;v<100*(n[4]*1.0/i);v++)
		printf("*");
		for(v=0;v<100-100*(n[4]*1.0/i);v++)
		printf("-");
		printf("]   %d  %c%f\n",n[4],o,100*n[4]*1.0/i);
	ListEnd:printf("\n\n\n\n\n");
}


void Delete(void)			/*	删除学生数据的函数，最后会保存到文件中	*/
{
	struct Student *h,*nexth,*head;
	int n;
	FILE *f;
	char s;
	head = h = ReadFile(h);
	nexth = h->next;
	printf("                                             Warning!!!                                         \n\n");
	printf("                          This operation will Delete the date of student.                       \n\n");
	printf("			             Are  you  sure  to  do  this?                              \n\n");
	printf("Press  Y  to  confirm,press  Anykey  to  give  up.  :");
		getchar();
		scanf("%c",&s);
	if(s=='y'||s=='Y')
	{
		printf("\n\n                               This  is  the  all  student's  infromation               \n\n");
		printf("\n\n			           What  do  you  want  to  delete  ?			\n\n");
		while(1)
		{
			output(h);
			printf("\n\n\nPlease input the Student ID you want to Delete:");
				scanf("%d",&n);
			printf("\n\n\nDo  you  want  to  Delete  the  information  of  the  NO.%d  Student?\n\n\n",n);
			printf("\n\n\nPlease  press  'Y'  to  confim  it,Or  press  AnyKey  to  input  again:");
					getchar();
					scanf("%c",&s);
			if(s=='y'||s=='Y')
			{
				for(;nexth!=NULL;)
				{
					if(nexth->num==n)
					{
						h->next=nexth->next;		/*将上一个节点直接指向后面的后面，掠过要删除的学生即可*/
						nexth=nexth->next;
					}
					h=h->next;
					if(nexth==NULL) break;
					nexth=nexth->next;
				}
				f=fopen("stu_dat","w+");
				while(head!=NULL)
				{
					fwrite(head,LEN,1,f);			/*最后将所有数据进行一次存盘*/
					head=head->next;
				}
				fclose(f);
				goto DeleteEnd;
			}
			if(s!='y'||s!='Y')
				goto DeleteEnd;
		}
	}
	if(s=='Y'||s=='y')
	DeleteEnd:printf("\n\n\n\n					Operation 		Successful	!		\n\n\n");
}	

int main()								/*主函数*/
{
	struct Student *h;
	int sum[5]={0},z;
	float ave[5]={0};
	char s;
	printf("\n\n\n\n\n\n\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("|					      	         ^ - ^	 							|\n");
	printf("|															|\n");
	printf("|		 													|\n");
//	printf("|           		        	    Welcom to the lili's Student Management System                            	|\n");
	printf("|           		        	    Welcom to the zhang's Student Management System                            	|\n");
	printf("|															|\n");
	printf("|						   ~~~~~       ~~~~~							|\n");
	printf("|						 ~~~~~~~~~   ~~~~~~~~~							|\n");
	printf("|					       ~~~~~~~~~~~~ ~~~~~~~~~~~							|\n");
	printf("|						 ~~~~~~~~~~~~~~~~~~~~							|\n");
	printf("|						     ~~~~~~~~~~~~~~							|\n");
	printf("|						       ~~~~~~~~~ 							|\n");
	printf("|					    	        ~~~~~~~ 							|\n");
	printf("|					            	  ~~~ 								|\n");
	printf("|					        	   ~	   							|\n");
	printf("|															|\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      Are  you  Admin?     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     If you are admin,Press  'l'  to  log on     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     If you merber,Press  Anykey  to  log on    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     If NOT,Come On,Press 'j' to join us     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~     If you are not interested in,(:@_@:)Press 'E' to exit this program     ~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	printf("\n\n\n\n\n");
	printf("Make your choice:");
                scanf("%c",&s);
	if(s!='E'&&s!='e')
	{
		if(s=='j'||s=='J')
		{
			Createuser();
		}
		if(s!='l'&&s!='L')
		{
			z=Configpasswd();
			if(z==1)
			{
				while(1)
				{
					Ustart:printf("***********************************************   What do you want to do?   *******************************************\n*\n***\n*****\n*******\n*********\n");
					printf("*-*-*-*-*-               A           :     Print      All     Student's   information.\n*\n");
					printf("*-*-*-*-*-               B           :     Sort    in      Student's      information.\n*\n");
					printf("*-*-*-*-*-               C           :     Find  the  information  you  want  to know.\n*\n");
					printf("*-*-*-*-*-               D           :     Lise    the   result   of   some   Subject.\n*\n*\n*\n*\n");
					printf("*-*-*-*-*-               Q           :     QUIT        this        system.    :>_<:\n*********\n*******\n*****\n***\n*\n");
					printf("***********************************************************************************************************************\n\n\n\n\n");
					printf("~~~~Hey~~~~Make   your   choice   ~^-^~  :");
						getchar();
						scanf("%c",&s);
					if(s=='A'||s=='a')
					{
						h=ReadFile(h);
						h=caculate(sum,ave,h);
						output(h);
       						printf("\nSum");
       						printf("%36d%20d%20d%20d%23d\n",sum[0],sum[1],sum[2],sum[3],sum[4]);
   	    					printf("Ave");
       						printf("%36f%20f%20f%20f%23f\n",ave[0],ave[1],ave[2],ave[3],ave[4]);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Ustart;		/*按任何键跳到用户开始的选择界面，由于有管理员和普通用户，所一开始的菜单不同，要分开*/
					}
					if(s=='B'||s=='b')
					{
						h=ReadFile(h);
						paixu(&h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Ustart;
					}
					if(s=='c'||s=='C')
					{
						h=ReadFile(h);
						Find(h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Ustart;
					}	
					if(s=='d'||s=='D')
					{
						h=ReadFile(h);
						List(h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Ustart;
					}
					if(s=='Q'||s=='q')
						goto end;
				}
			}
			if(z==0)
				goto end;
		}
		if(s=='l'||s=='L')
		{
				z=ConfigAdmin();
			if(z==1)
			{
				while(1)
				{
					Astart:printf("***********************************************   What do you want to do?   *******************************************\n*\n***\n*****\n*******\n*********\n");
					printf("*-*-*-*-*-               A           :     Input   or   add   Student's   informatino.\n*\n");
					printf("*-*-*-*-*-               B           :     Print      All     Student's   information.\n*\n");
					printf("*-*-*-*-*-               C           :     Change        Student's        information.\n*\n");
					printf("*-*-*-*-*-               D           :     Delete        Student's        information.\n*\n");
					printf("*-*-*-*-*-               E           :     Sort    in      Student's      information.\n*\n");
					printf("*-*-*-*-*-               F           :     Find  the  information  you  want  to know.\n*\n");
					printf("*-*-*-*-*-               G           :     Lise    the   result   of   some   Subject.\n*\n*\n*\n*\n");
					printf("*-*-*-*-*-               Q           :     QUIT        this        system.    :>_<:\n*********\n*******\n*****\n***\n*\n");
					printf("***********************************************************************************************************************\n\n\n\n\n");
					printf("~~~~Hey~~~~Make   your   choice   ~^-^~  :");
						getchar();
						scanf("%c",&s);
					if(s=='A'||s=='a')
					{
						h=input();
						h=ReadFile(h);
						caculate(sum,ave,h);
						printf("Press  Anykey  to  Pop-up Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='b'||s=='B')
					{
						h=ReadFile(h);
						h=caculate(sum,ave,h);
						output(h);
       						printf("\nSum");
       						printf("%36d%20d%20d%20d%23d\n",sum[0],sum[1],sum[2],sum[3],sum[4]);
   	    					printf("Ave");
       						printf("%36f%20f%20f%20f%23f\n",ave[0],ave[1],ave[2],ave[3],ave[4]);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='C'||s=='c')
					{
						Change();
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='D'||s=='d')
					{
						Delete();
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='e'||s=='E')
					{
						h=ReadFile(h);
						paixu(&h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='f'||s=='F')
					{
						h=ReadFile(h);
						Find(h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}	
					if(s=='G'||s=='g')
					{
						h=ReadFile(h);
						List(h);
						printf("Press  Anykey  to  Pop-up  Main  select  directory.");
						getchar();
						scanf("%c",&s);
						goto Astart;
					}
					if(s=='Q'||s=='q')
						goto end;
				}
			}
			if(z==0)
				goto end;
		}
	}
		if(s=='E'||s=='e')
			end :return 0;
}
