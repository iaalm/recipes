#include <stdio.h>
int test1()
{
	puts("1");
	return 0;
}

int test2()
{
	int i;
	puts("2");
	*(&i+4) += 5;
	return 3; 
}

int main()
{
	test2();
	test1();
	test1();
	return 0;
}
