paixu(struct Student **h)
{
        char s;
	struct Student *nexth,*lasth1,*lasth2,*head,*r;
	int i=0;
	head=lasth1=lasth2=*h;
	printf("\n~~~~~~~~~~~~~~~what way do you want to use to sort in?~~~~~~~~~~~~~\n");
	printf("Please input your chorice \nA :Sum score Max->Min~~~~B :Sum score Min->Max~~~~C :In accordance with Student ID):");
		getchar();
                scanf("%c",&s);
	printf("\n~~~~~~~~This is the information you want to know~~~~~~~~\n");
	if(s=='A')
	{
		for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
	 	{
			for(nexth=head->next;nexth!=NULL;)
			{
				if(head==*h&&head->sum<nexth->sum)				//如果是第一个，并且第一个大于第二个，则单独进行指向的改变()
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
				if(head!=(*h)&&head->sum<nexth->sum)				//不是第一个的，作为另外一种情况考虑
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
	}


		
	if(s=='B')
	{
		for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
 		{
			for(nexth=head->next;nexth!=NULL;)
			{
				if(head==*h&&head->sum>nexth->sum)				//如果是第一个，并且第一个大于第二个，则单独进行指向的改变()
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
				if(head!=(*h)&&head->sum>nexth->sum)				//不是第一个的，作为另外一种情况考虑
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
	}	
		
	
	if(s=='C')
	{
	 	for(;head!=(*h)->next;)								//此循环用来将最小的放第一个，为了避免变量问题，下面单独用一个循环排序
	 	{
			for(nexth=head->next;nexth!=NULL;)
			{
				if(head==*h&&head->num>nexth->num)				//如果是第一个，并且第一个大于第二个，则单独进行指向的改变()
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
				if(head!=(*h)&&head->num>nexth->num)				//不是第一个的，作为另外一种情况考虑
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
	}
	output(*h);
}
