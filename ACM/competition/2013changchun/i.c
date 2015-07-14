#include<stdio.h>

int f(int n,int m)
{
    if(m==1||n==m)
        return 1;
    else
	    return f(n-1,m-1)+f(n-1,m)*m;
}

int main(void)
{
	int n,count;
	scanf("%d",&count);
	while(count--)
	{
		scanf("%d",&n);
		int i;
		int sum=0;
		for(i=1;i<=n;i++)
		{
			sum+=f(n,i);
			sum %=  95041567;
		}
		printf("%d\n",sum);
	}
	return 0;
}
