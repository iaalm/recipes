#include <stdio.h>

int main (int argc, char const* argv[])
{
	int a=7;
	a+=a-=a+a;          //等价于a-=(a+a);a+=a;
	printf("%d",a);
	return 0;
}
