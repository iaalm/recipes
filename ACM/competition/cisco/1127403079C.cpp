#include<stdio.h>

int main()
{
	unsigned int t,n,c;
	scanf("%d",&t);
	while(t != 0)
	{
		scanf("%d",&n);
		c = 0;
		while((n & 1) == 0)
		{
			n >>= 1;
			c++;
		}
		printf("%d\n",1 << c);
		t--;
	}
}