#include<stdio.h>
#include<string.h>

int main()
{
	int i;
	memset(&i,0,sizeof(i));
	printf("%X\n",i);
	memset(&i,1,sizeof(i));
	printf("%X\n",i);
	memset(&i,-1,sizeof(i));
	printf("%X\n",i);
}
