#include<stdio.h>

int main()
{
	int i,j,t,result;
	scanf("%d",&i);
	while(i != 0)
	{
		scanf("%d",&j);
		result = 1 - j;
		while(j != 0)
		{
			scanf("%d",&t);
			result+=t;
			j--;
		}
		printf("%d\n",result);
		i--;
	}
	return 0;
}
