#include<stdio.h>
#include<string.h>

int n,b[24];

inline int count(int m)
{
	int k = 0,i;
	for(i = 0;i < 26;i++)
		if((1 << i) & m)
			k++;
	return k;
}

int S(int l,int p,int r)
{
	int i,t,best = -1,bn = 30;
	for(i = p;i < n;i++)
		if((l ^ b[i]) == 0)
			return (r | (1 << i));
	for(i = p;i < n;i++)
		if((t = S(l ^ b[i],i + 1,r | (1 << i))) != -1)
			if(count(t) < bn)
			{
				bn = count(t);
				best = t;
			}
	return best;
}

int main()
{
	int i,j,k,target = 0;
	char t[26];
	scanf("%d",&n);
	memset(b,0,sizeof(b));
	for(i = 0;i < n;i++)
	{
		scanf("%s",t);
		j = strlen(t);
		while(j--)
			b[i] |= (1 << (t[j] -'A'));
		target ^= b[i];
	}
	if(target != 0)
		j = S(target,0,0);
	else
		j = 0;
	k =  n - count(j);
	printf("%d\n",k);
	for(i = 0;i < n;i++)
		if(!(j & (1 << i)))
			printf("%d ",i + 1);
	putchar(10);
	return 0;
}
