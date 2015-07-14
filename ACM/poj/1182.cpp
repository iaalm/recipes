#include<stdio.h>

int fa[50010],re[50010];

int find(int n)
{
	int s;
	if(fa[n] == 0)
		return n;
	s = find(fa[n]);
	re[n] += re[fa[n]];
	re[n] %= 3;
	return fa[n] = s;
}

int main()
{
	int N,M,i,j,k,m,n,wrong = 0;
	scanf("%d %d",&N,&M);
	while(M--)
	{
		scanf("%d %d %d",&i,&j,&k);
		if(j > N || k > N)
		{
			wrong++;
			continue;
		}
		i--;
		m = find(j);
		n = find(k);
		if(m == n)
		{
			if( (re[j] + i) % 3 != re[k])
				wrong++;
		}
		else
		{
			fa[n] = m;
			re[n] = (i +re[j] - re[k] + 3) % 3;
		}
	}
	printf("%d\n",wrong);
}
