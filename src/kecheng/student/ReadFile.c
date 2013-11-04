struct Student *ReadFile(struct Student *h)
{
	struct Student *p1,*p2,*p3;
	FILE *Read;
	fopen("stu_dat","r+");
	h=p1=p2=p3=(struct Student *)malloc(LEN);
	for(;fread(p2,LEN,1,Read)!='\0';)
	{
                p1=(struct Student *)malloc(LEN);
		p2->next=p1;
                p2=p1;
	}
	while(p3->next!=p2)
		p3=p3->next;
	p3->next=NULL;
	p2=NULL;
	return (h);
}
