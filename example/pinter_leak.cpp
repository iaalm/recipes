#include <stdio.h>

int main()
{
	int a;
	int *p=&a;
	for(int i=0;i<=20;i++)
	printf("%X ",*(p+i));
	return 0;
}