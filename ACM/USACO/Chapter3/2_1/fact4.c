/*
ID: simonin1
LANG: C
TASK: fact4
*/

#include<stdio.h>
#include<assert.h>

int ft = 0;
int pft(int n)
{
	while(~n & 1)		//n % 2 == 0
	{
		n >>= 1;
		ft++;
	}
	while(n % 5 == 0)
	{
		n /= 5;
		ft--;
	}
	return n;
}

int main()
{
	int max,tail = 1,i;
	FILE *fp = fopen("fact4.in","r");
	fscanf(fp,"%d",&max);
	fclose(fp);

	for(i = 2;i <= max;i++)
	{
		tail *= pft(i);
		tail %= 10;
	}
	assert(ft >= 0);
	ft %= 4;
	ft += 4;
	
	while(ft--)
		tail *= 2;
	tail %= 10;
	if(max == 1)
		tail = 1;

	fp = fopen("fact4.out","w");
	fprintf(fp,"%d\n",tail);
	fclose(fp);
}
