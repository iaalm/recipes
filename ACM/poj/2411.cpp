#include<stdio.h>
#include<string.h>

long long dpt[2048][11][11];

long long dp(unsigned short level,short rem,short w);
long long fill(unsigned short level,short rem,short w,short start,short sl)
{
	while(start != w && (level & (1 << start)))
		start++;
	if(start == w)
		return dp(sl,rem - 1,w);
	else
	{
		if(start != w - 1 && !(level & (1 << (start + 1))))
			return (fill(level,rem,w,start + 2,sl) + fill(level,rem,w,start + 1,sl | (1 << start)));
		else
			return fill(level,rem,w,start + 1,sl | (1 << start));
	}
}

long long dp(unsigned short level,short rem,short w)
{
	long long *res = &dpt[level][rem][w],i,j;
	if(*res != -1)
		return *res;
	if(rem == 1)
	{
		for(i = 0;i < w;i++)
			if(!(level & (1 << i)))
			{
				j = i + 1;
				while(j != w && !(level & (1 << j)))
					j++;
				if((j - i) % 2)
					return (*res = 0);
				i = j;
			}
		return (*res = 1);
	}
	return (*res = fill(level,rem,w,0,0u));
}

int main()
{
	memset(dpt,0xff,sizeof(dpt));
	short w,h;
	while(1)
	{
		scanf("%hd %hd",&w,&h);
		if((w * h) % 2)
		{
			printf("0\n");
			continue;
		}
		if(w == 0)
			return 0;
		if(w > h)
		{
			w ^= h;
			h ^= w;
			w ^= h;
		}
		printf("%lld\n",dp(0u,w,h));
	}
}
