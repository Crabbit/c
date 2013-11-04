struct Student *input(void)
{
	struct Student *head,*p1,*p2;
	int i,n;
	p1=p2=(struct Student *)malloc(LEN);
	head=NULL;
	printf("\n~~~~~~~~Welcom to the student manage system~~~~~~~~\n");
	printf("~~~~~~How many student do you want to input?~~~~~~~\n");
	printf("~~~~~~~~Please input the number :");
		scanf("%d",&n);
	printf("~~~~~~~~~Please input student information~~~~~~~~~\n");
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
