/*
ID: simonin1
LANG: C
TASK: zerosum
*/

#include<stdio.h>
#include<assert.h>

int n;
char sign[9];
FILE *fp;

void work(int l);
int check(int start,int s);

int main()
{
	fp = fopen("zerosum.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);

	fp = fopen("zerosum.out","w");
	work(1);
	fclose(fp);

	return 0;
}

void work(int l)
{
	if(l != n)
	{
		sign[l] = ' ';
		work(l + 1);
		sign[l] = '+';
		work(l + 1);
		sign[l] = '-';
		work(l + 1);
	}
	else
	{
		if(check(1,0) == 0)
		{
			for(l = 1;l < n;l++)
				fprintf(fp,"%d%c",l,sign[l]);
			fprintf(fp,"%d\n",n);
		}
	}
}

int check(int start,int s)
{
	int t = start,i;
	if(start == n)
	{
		if(s)
			start = -start;
		return start;
	}
	for(i = start;i < n;i++)
	{
		if(sign[i] == ' ')
			t = t * 10 + i + 1;
		else if(sign[i] == '+')
		{
			if(s)
				t = -t;
			return (t + check(i + 1,0));
		}
		else
		{
			if(s)
				t = -t;
			assert(sign[i] == '-');
			return (t + check(i + 1,1));
		}
	}
	assert(i == n);
	if(s)
		t = -t;
	return t;
}
