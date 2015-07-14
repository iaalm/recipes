/*
ID: simonin1
LANG: C
TASK: money
*/

#include<stdio.h>
#include<stdlib.h>

int v,m[25];
long long *table;

long long work(int num,int i);

int main()
{
	int num,i,j,max_index;
	FILE *fp = fopen("money.in","r");
	fscanf(fp,"%d %d",&v,&num);
	for(i = 0;i < v;i++)
		fscanf(fp,"%d",m + i);
	fclose(fp);
	table = (long long*) malloc(sizeof(long long) * num * v);
	for(i = 0;i < num * v;i++)
		table[i] = -1;

	//sort m[]
	for(i = 0;i < v;i++)
	{
		max_index = i;
		for(j = i + 1;j < v;j++)
		        if(m[max_index] < m[j])
		                max_index = j;
		if(max_index != i)
		{
			j = m[i];
			m[i] = m[max_index];
			m[max_index] = j;
		}
	}
/*	for(i = 0;i < v;i++)
	        printf("%d ",m[i]);
*/

	fp = fopen("money.out","w");
	fprintf(fp,"%lld\n",work(num,0));
	fclose(fp);

	free(table);
	return 0;
}

long long work(int num,int i)
{
	if(num < 0)
		return 0;
	else if(num == 0)
		return 1;
	else if(table[(num - 1) * v + i] != -1)
		return table[(num - 1) * v + i];
	else
	{
		long long result = 0;
		int j;
		for(j = i;j < v;j++)
			result += work(num - m[j],j);
		table[(num - 1) * v + i] = result;
		return result;
	}
}
