void output(struct Student *h)
{
	printf("NO.\t\tname\t\tMTscore\t\tENscore\t\tPHscore\t\tSum\t\tAve\n");
	for(;h!=NULL;)
	{
		printf("%d%19s%20d%23d%23d%23d%19d%19f\n",h->num,h->name,h->MT,h->EN,h->PH,h->sum,h->ave);
		h=h->next;
	}
}
