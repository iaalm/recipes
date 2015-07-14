#include<cstdio>
#include<cstdlib>
#include<cstring>

int main()
{
	char pri[10000];
	memset(pri,1,sizeof(pri));
	short T,s,e,i,j,now,f[10000],qu[10000];
	pri[1] = pri[0] = 0;
	for(i = 2;i < 10000;i++)
		if(pri[i])
			for(j = i * 2;j < 10000;j += i)
				pri[j] = 0;
	scanf("%hd",&T);
	while(T--)
	{
		now = 1;
		memset(f,0,sizeof(f));
		scanf("%hd %hd",&s,&e);
		if(s == e)
		{
			puts("0");
			continue;
		}
		if(!pri[e])
			goto end;
		qu[0] = s;
		f[s] = 1;
		for(i = 0;i < now;i++)
		{
			for(s = qu[i] % 1000 + 1000,j = 1;j < 10;j++,s += 1000)
				if(pri[s] && !f[s])
				{
					if(s == e)
					{
						f[e] = 1;
						printf("%hd\n",f[qu[i]]);
						goto end;
					}
					f[s] = f[qu[i]] + 1;
					qu[now++] = s;
				}
			for(s = qu[i] - (qu[i] / 100) % 10 * 100,j = 0;j < 10;j++,s += 100)
				if(pri[s] && !f[s])
				{
					if(s == e)
					{
						f[e] = 1;
						printf("%hd\n",f[qu[i]]);
						goto end;
					}
					f[s] = f[qu[i]] + 1;
					qu[now++] = s;
				}
			for(s = qu[i] - (qu[i] / 10) % 10 * 10,j = 0;j < 10;j++,s += 10)
				if(pri[s] && !f[s])
				{
					if(s == e)
					{
						f[e] = 1;
						printf("%hd\n",f[qu[i]]);
						goto end;
					}
					f[s] = f[qu[i]] + 1;
					qu[now++] = s;
				}
			for(s = qu[i] - qu[i] % 10,j = 0;j < 10;j++,s += 1)
				if(pri[s] && !f[s])
				{
					if(s == e)
					{
						f[e] = 1;
						printf("%hd\n",f[qu[i]]);
						goto end;
					}
					f[s] = f[qu[i]] + 1;
					qu[now++] = s;
				}
		}
end:		if(!f[e])
			puts("Impossible");
	}
	return 0;
}
