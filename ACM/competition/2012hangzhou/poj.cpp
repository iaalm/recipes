#include<cstdio>
#include<cstdlib>
#include<cmath>

int main()
{
	int n,i,j,po[8][2];
	long long k,t,min,xs,xe,ys,ye;
	while(1)
	{
		min = 0;
		scanf("%d",&n);
		if(n == 0)
			return 0;
		scanf("%d%d",&po[0][0],&po[0][1]);
		xs = xe = po[0][0];
		ys = ye = po[0][1];
		for(i = 1;i < n;i++)
		{
			scanf("%d%d",&po[i][0],&po[i][1]);
			if(po[i][0] < xs)
				xs = po[i][0];
			if(po[i][0] > xe)
				xe = po[i][0];
			if(po[i][1] < ys)
				ys = po[i][1];
			if(po[i][1] > ye)
				ye = po[i][1];
		}
		for(i = 0;i < n;i++)
		{
			k = ((long long)1) << 60;
			if(i % 2 == 0)
				j = 1;
			else
				j = 0;
			for(;j < n;j+=2)
			{
				t = (po[i][0] - po[j][0]) * (po[i][0] - po[j][0]) + (po[i][1] - po[j][1]) * (po[i][1] - po[j][1]);
				if(t < k)
					k = t;
			}
			if(k > min)
				min = k;
		}
		if(min > (xe - xs)*(xe-xs))
			min = (xe - xs)*(xe-xs);
		if(min > (ye - ys)*(ye-ys))
			min = (ye - ys)*(ye-ys);
		printf("%.2lf\n",sqrt((double)min));
	}
}
