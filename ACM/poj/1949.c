#include<stdio.h>

int main()
{
	int n,i,j,d,dc,t;
	scanf("%d",&n);
	int ft[n];
	for(i = 0;i < n;i++)
	{
		scanf("%d %d",&t,&dc);
		ft[i] = t;
		for(j = 0;j < dc;j++)
		{
			scanf("%d",&d);
			d--;
			if(ft[i] < ft[d] + t)
				ft[i] = ft[d] + t;
		}
	}
	j = 0;
	for(i = 0;i < n;i++)
		if(ft[i] > j)
			j = ft[i];
	printf("%d\n",j);
	return 0;
}
