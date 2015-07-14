/*
ID: simonin1
LANG: C
TASK: kimbits
*/

#include<stdio.h>

unsigned int tab[32][32];

unsigned int c(unsigned int l,unsigned int s)
{
	if(l < s)
		s = l;
	if(!tab[l][s])
		tab[l][s] = c(l - 1,s - 1) + c(l - 1,s);
	return tab[l][s];
}

int main()
{
	unsigned int i,len,one,num;
	FILE *fp = fopen("kimbits.in","r");
	fscanf(fp,"%u%u%u",&len,&one,&num);
	fclose(fp);

	//bzero(*tab,sizeof(tab));
	for(i = 0;i < 32;i++)
		tab[i][0] = 1;
	fp = fopen("kimbits.out","w");
	while(len--)
	{
		if(c(len,one) >= num)		//not > or the answer will add 1
		{
			fputc('0',fp);
		}
		else
		{
			num -= c(len,one);
			one--;
			fputc('1',fp);
		}
	}
	fputc(10,fp);
	fclose(fp);

	return 0;
}
