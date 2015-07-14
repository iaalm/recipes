#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF (1 << 26)
#define TRANS(R,L,N) ((R)*(N)+(L))
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

int main()
{
	int n,i,j,*tab,m;
	char t;
	while(1)
	{
		scanf("%d",&n);
		if(n == 0)
			return 0;
		tab = (int*)malloc(n * n * sizeof(int));
		memset(tab,0x0f,n * n * sizeof(int));
		for(i = 0;i < n - 1;i++)
		{
			scanf(" %*c %d",&m);
			while(m--)
			{
				scanf(" %c %d",&t,&j);
				tab[i * n + t - 'A'] = j;
				tab[(t - 'A') * n + i] = j;
			}
		}
		printf("%d\n",Prim(tab,n));
		free(tab);
	}
}
