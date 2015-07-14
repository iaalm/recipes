#include<stdio.h>
#include<math.h>

inline int max(int a,int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

inline int yf(int a,int b)
{
	int t;
	while(b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	if(a < 0)
		a = -a;
	return a;
}

int DFS(int p,int q,int a,int c,int fin)
{
	int count = 0,i,m,n,y,sa = sqrt(a);
	if(c <= 0)
		return 0;
	if(p == 1 && q <= a && q >= fin)
		count = 1;
	for(i = max(q/p,fin);i <= sa;i++)//
	{
		m = i * p - q;
		n = i * q;
		y = yf(m,n);
		if(y != 0)
		{
			m /= y;
			n /= y;
		}
//		if(m == 0)
//			count++;
		if(m > 0)
			count += DFS(m,n,a / i,c - 1,i);

	}
	return count;

}

int main()
{
	int p,q,a,n,y;
	while(1)
	{
		scanf("%d %d %d %d",&p,&q,&a,&n);
		if(p == 0)
			return 0;
		y = yf(p,q);
		if(y != 0)
		{
			p /= y;
			q /= y;
		}
		printf("%d\n",DFS(p,q,a,n,1));
	}
}
