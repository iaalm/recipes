/*
ID: simonin1
LANG: C
TASK:hamming
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

unsigned short num = 1,d,b;
unsigned short ham(unsigned short a,unsigned short c);
unsigned short check(unsigned short *p,unsigned short a);

int main()
{
	unsigned short n,bm,i,*result;
	FILE *fp = fopen("hamming.in","r");
	fscanf(fp,"%hd %hd %hd",&n,&b,&d);
	fclose(fp);

	result = (unsigned short*)malloc(sizeof(unsigned short) * n);
	result[0] = 0;
	bm = 1 << b;
	for(i = 1;i < bm;i++)
		if(check(result,i))
		{
			result[num] = i;
			num++;
			if(num == n)
				break;
		}

	fp = fopen("hamming.out","w");
	for(i = 0;i < n;i++)
	{
		fprintf(fp,"%hd",result[i]);
		if(i % 10 == 9 || i == n - 1)
			fprintf(fp,"\n");
		else
			fprintf(fp," ");
	}
	fclose(fp);
	free(result);
}

unsigned short ham(unsigned short a,unsigned short c)
{
	unsigned short result = 0,i,t = a ^ c;
	for(i = 0;i < b;i++)
		if(t & (1 << i))
			result++;
	return result;
}
unsigned short check(unsigned short *p,unsigned short a)
{
	unsigned short i;
	for(i = 0;i < num;i++)
	{
		if(ham(p[i],a) < d)
			return 0;
	}
	return 1;
}
