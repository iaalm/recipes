/*
ID: simonin1
LANG: C
TASK:preface
*/

#include<stdio.h>
#include<assert.h>

struct num
{
	int i,v,x,l,c,d,m;
};

void work(int num,struct num *f);

int main()
{
	int n,i;
	struct num result = {0,0,0,0,0,0,0};
	FILE *fp = fopen("preface.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);

	for(i = 1;i <= n;i++)
		work(i,&result);

	fp = fopen("preface.out","w");
	if(result.i != 0)
		fprintf(fp,"I %d\n",result.i);
	if(result.v != 0)
		fprintf(fp,"V %d\n",result.v);
	if(result.x != 0)
		fprintf(fp,"X %d\n",result.x);
	if(result.l != 0)
		fprintf(fp,"L %d\n",result.l);
	if(result.c != 0)
		fprintf(fp,"C %d\n",result.c);
	if(result.d != 0)
		fprintf(fp,"D %d\n",result.d);
	if(result.m != 0)
		fprintf(fp,"M %d\n",result.m);
	fclose(fp);
	
	return 0;
}

void work(int num,struct num *f)
{
	if(num >= 1000)
	{
		f -> m++;
		work(num - 1000,f);
	}
	else if(num >= 900)
	{
		f -> m++;
		f -> c++;
		work(num - 900,f);
	}
	else if(num >= 500)
	{
		f -> d++;
		work(num - 500,f);
	}
	else if(num >= 400)
	{
		f -> d++;
		f -> c++;
		work(num - 400,f);
	}
	else if(num >= 100)
	{
		f -> c++;
		work(num - 100,f);
	}
	else if(num >= 90)
	{
		f -> c++;
		f -> x++;
		work(num - 90,f);
	}
	else if(num >= 50)
	{
		f -> l++;
		work(num - 50,f);
	}
	else if(num >=40)
	{
		f -> l++;
		f -> x++;
		work(num - 40,f);
	}
	else if (num >= 10)
	{
		f -> x++;
		work(num - 10,f);
	}
	else if(num >= 9)
	{
		f -> x++;
		f -> i++;
		work(num - 9,f);
	}
	else if(num >= 5)
	{
		f -> v++;
		work(num - 5,f);
	}
	else if(num >= 4)
	{
		f -> v++;
		f -> i++;
		work(num - 4,f);
	}
	else if(num >= 1)
	{
		f -> i += num;
	}
	else
		return;
}
