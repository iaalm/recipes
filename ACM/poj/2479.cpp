#include<stdio.h>

long long dpt[60000][4];

inline long long max(long long a,long long b)
{
	if(a >= b)
		return a;
	else
		return b;
}

int main()
{
	int T,n,i,tab[60000];
	long long m,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i = 0;i < n;i++)
			scanf("%d",tab + i);
		dpt[0][0] = tab[0];
		dpt[0][1] = tab[0];
		dpt[n - 1][2] = tab[n - 1];
		dpt[n - 1][3] = tab[n - 1];
		for(i = 1;i < n;i++)
		{
			dpt[i][0] = max(dpt[i - 1][0],dpt[i - 1][1]);
			dpt[i][1] = max(dpt[i - 1][1],0) + tab[i];
			dpt[n - i - 1][2] = max(dpt[n - i][2],dpt[n - i][3]);
			dpt[n - i - 1][3] = max(dpt[n - i][3],0) + tab[n - i - 1];

		}
		for(m = (long long)1 << 63,i = 0;i < n - 1;i++)
			if((j = dpt[i][1] + dpt[i][2]) > m)
				m = j;
		printf("%lld\n",m);
	}
	return 0;
}
