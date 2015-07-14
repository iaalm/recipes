#include <stdio.h>

int main (int argc, char const* argv[])
{
	float x=2.7;
	if(x!=(2.7))                 //问题存在于double到float的转换
		printf("x!=2.7!");
	return 0;
}
