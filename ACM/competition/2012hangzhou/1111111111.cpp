#include<cstdio>
#include<cstdlib>
#include<cmath>

int main()
{
	int n,i,j,po[8][2];
	long long k,t,min;
	while(1)
	{
		min = 0;
		scanf("%d",&n);
		if(n == 0)
			return 0;
		for(i = 0;i < n;i++)
			scanf("%d%d",&po[i][0],&po[i][1]);
		for(i = 0;i < n;i++)
		{
			k = ((long long)1) << 60;
			for(j = 0;j < n;j++)
			{
				if(i == j)
					continue;
				t = (po[i][0] - po[j][0]) * (po[i][0] - po[j][0]) + (po[i][1] - po[j][1]) * (po[i][1] - po[j][1]);
				if(t < k)
					k = t;
			}
			if(k > min)
				min = k;
		}
		if(n == 8)
		{
			k = ((long long)1) << 60;
			for(i = 0;i < n;i++)
			{
				j = i + 3;
				t = (po[i][0] - po[j][0]) * (po[i][0] - po[j][0]) + (po[i][1] - po[j][1]) * (po[i][1] - po[j][1]);
				if(t < k)
					k = t;
				j = i + 1;
				t = (po[i][0] - po[j][0]) * (po[i][0] - po[j][0]) + (po[i][1] - po[j][1]) * (po[i][1] - po[j][1]);
				if(t < k)
					k = t;
			}
		}
		if(k > min)
			min = k;
		printf("%.2lf\n",sqrt((double)min));
	}
}
