#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

int main()
{
	int w,h,hn,i,j,k,l,e[1024],hole[1024],visit[1024],qu[1024],now,it,m,n,p,result;
	const short 	setx[4] = {-1, 0, 0, 1},
	      		sety[4] = { 0,-1, 1, 0};
	scanf("%d %d %d",&w,&h,&hn);
	result = w * h - hn;
	if(result % 2)
	{
		puts("NO");
		return 0;
	}
	result /= 2;

	k = 0;
	clr(hole);
	memset(e,0xff,sizeof(e));
	while(hn--)
	{
		scanf("%d %d",&i,&j);
		i--;
		j--;
		hole[(i << 5) + j] = 1;
		if((i - j) % 2)
			k--;
		else
			k++;
	}
	if((w * h) % 2)
	{
		if(k != 1)
		{
			puts("NO");
			return 0;
		}
	}
	else
	{
		if(k != 0)
		{
			puts("NO");
			return 0;
		}
	}
	for(m = 0;m < h;m++)
		for(n = m  % 2;n < w;n += 2)
		{
			i = (m << 5) + n;
			if(hole[i])
				continue;
			memset(visit,0xff,1024 * sizeof(int));
			now = 1;
			qu[0] = i;
			visit[i] = i;
			for(j = 0;j < now;j++)
			{
				for(p = 0;p < 4;p++)
				{
					it = (((qu[j] >> 5) + setx[p]) << 5) + (qu[j] & 31) + sety[p];
					if((qu[j] >> 5) + setx[p] < 0 || (qu[j] >> 5) + setx[p] >= h || (qu[j] & 31) + sety[p] < 0 || (qu[j] & 31) + sety[p] >= w || hole[it])
						continue;
					if(e[it] == -1)
					{
						k = it;
						for(l = qu[j];l != i;l = visit[l])
						{
							e[k] = l;
							swap(k,e[l]);
						}
						e[k] = i;
						swap(k,e[i]);
						result--;
						goto end;
					}
					k = e[it];
					if(visit[k] == -1)
					{
						visit[k] = qu[j];
						qu[now++] = k;
					}
				}
			}
			break;
end:			;
		}
	if(result)
		puts("NO");
	else
		puts("YES");
	return 0;
}
