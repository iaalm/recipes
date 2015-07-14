#include<stdio.h>

int max;

void fn(int num,int p,int s);//num未使用水果数，p剩余盘子数

int main()
{
	int t,n,p;
	scanf("%d",&t);
	while(t != 0)
	{
		scanf("%d %d",&n,&p);
		max = 0;
		fn(n,p,0);
		printf("%d\n",max);
		t--;
	}
}

void fn(int num,int p,int s)//s保证对盘子进行排序
{
	if(s > num)
		return;
	if(p == 1)
	{					//此时s <= num
		max++;
		return;
	}
	for(;s <= num / p;s++)
	{
		fn(num - s,p - 1,s);
	}
}