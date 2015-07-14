#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n,i,g;
	float c,tc,tg,result;
	while(scanf("%d",&n) != EOF)
	{
		tc = tg = 0;
		for(i = 0;i < n;i++)
		{
			scanf("%f %d",&c,&g);
			tc += c;
			if(g >= 60)
				tg += c * g;
		}
		scanf("%f %d",&c,&g);
		tc += c;
		result = (tc * 70 - tg - c * (10 + 20.0 * g / 100)) / 0.7 / c;
		if(result < 60 || result > 100)
			printf("0\n");
		else
		{
			i = result;
			if(i < result)
				i++;
			printf("%d\n",i);
		}
	}
	return 0;
}