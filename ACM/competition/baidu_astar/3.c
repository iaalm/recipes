#include<stdio.h>

int main()
{
	int i;
	double t,result = 0;
	for(i = 0;i < 12;i++)
	{
		scanf("%lf",&t);
		result += t;
	}
	result /= 12;
	printf("$%.2lf\n",result);
	return 0;
}
