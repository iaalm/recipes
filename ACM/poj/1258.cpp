/*
ID: simonin1
LANG: C
TASK:agrinet
*/

#include<stdio.h>
#include<stdlib.h>
#define INF (1 << 26)
#define TRANS(R,L,N) ((R)*(N)+(L))

int Prim(int *table,int num);

int main()
{
	int n,i,j,*table;
	while(scanf("%d",&n) != EOF)
	{
	table = (int*) malloc(sizeof(int) * n * n);
	for(i = 0;i < n;i++)
	{
	        for(j = 0;j < n;j++)
	               scanf("%d",table + TRANS(i,j,n));
	}

	printf("%d\n",Prim(table,n));
	free(table);
	}
}

int Prim(int *table,int num)
{
	int i,min,index,s,result = 0;
	int *low = (int*)malloc(num * sizeof(int));
	for(s = 1;s < num;s++)
		low[s] = table[TRANS(0,s,num)];
	low[0] = 0;
	for(s =1;s < num;s++)
	{
		min = INF;
		for(i = 0;i < num;i++)
			if(low[i] != 0 && low[i] < min)
			{
				min = low[i];
				index = i;
			}
		result += min;
		low[index] = 0;
		for(i = 0;i < num;i++)
			if(table[TRANS(i,index,num)] < low[i])
				low[i] = table[TRANS(i,index,num)];
	}
	free(low);
	return result;
}
