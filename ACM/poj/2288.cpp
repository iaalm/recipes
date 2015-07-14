#include<stdio.h>
#include<string.h>

typedef struct
{
	int max,num;
} ans;
ans dpt[2 << 13][13][13];
short map[13][13],value[13],in,bn,nmap[13];

ans dp(short p,short p1,short p2)
{
	ans* const res = &dpt[p][p1][p2];
	if(res->num != -1)
		return *res;
	if(p == 0)
	{
		res -> num = 1;
		res -> max = value[p1] * value[p2];
		return *res;
	}
	res -> num = 0;
	res -> max = 0;
	int i,j,k,l = value[p1] * value[p2];
	ans t;
	for(i = 0;i < nmap[p2];i++)
	{
		k = map[p2][i];
		if(!(p & (1 << k)))
			continue;
		t = dp(p & ~(1 << k),p2,k);
		if(!t.num)
			continue;
		for(j = 0;j < nmap[k];j++)
			if(p1 == map[k][j])
			{
				t.max += l * value[k];
				break;
			}
		t.max += l;
		if(t.max == res -> max)
			res->num += t.num;
		if(t.max > res -> max)
			memcpy(res,&t,sizeof(ans));
	}
	return *res;
}

int main()
{
	short T,j,k,sum;
	long long i,l;
	ans t;
	scanf("%hd",&T);
	while(T--)
	{
		memset(dpt,0xff,sizeof(dpt));
		memset(map,0,sizeof(map));
		memset(nmap,0,sizeof(nmap));
		sum = 0;
		scanf("%hd %hd",&in,&bn);
		for(i = 0;i < in;i++)
			scanf("%hd",value + i);
		for(i = 0;i < in;i++)
			sum += value[i];
		for(i = 0;i < bn;i++)
		{
			scanf("%hd %hd",&j,&k);
			j--;
			k--;
			map[j][nmap[j]++] = k;
			map[k][nmap[k]++] = j;
		}
		if(in == 1)
		{
			printf("%d 1\n",value[0]);
			continue;
		}
		for(i = 0,l = 0,j= 0;j < in;j++)
			for(k = 0;k < nmap[j];k++)
			{
				t = dp((((1 << in) - 1) & ~((1 << j) | (1 << map[j][k]))),j,map[j][k]);
				if(t.max == i)
					l += t.num;
				if(t.max > i)
				{
					i = t.max;
					l = t.num;
				}
			}
		i += sum;
		if(l)
			printf("%lld %lld\n",i,l >> 1);
		else
			printf("0 0\n");
	}
	return 0;
}
