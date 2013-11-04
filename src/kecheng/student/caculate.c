void caculate(int sum[],float ave[],struct Student *h)
{
	for(;h!=NULL;)
	{
		h->sum=h->MT+h->EN+h->PH;
		h->ave=h->sum/3.0;
		sum[0]=sum[0]+h->MT;
		sum[1]=sum[1]+h->EN;
		sum[2]=sum[2]+h->PH;
		h=h->next;
	}
}
