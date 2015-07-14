#include<stdio.h>
int main()
{
	int h,m,i;
	scanf("%d",&i);
	while(i != 0)
	{
		scanf("%d:%d",&h,&m);
		if(m != 0)
			printf("0\n");
		else
			printf("%d\n",(h+11) % 24 + 1);
		i--;
	}
	return 0;
}
