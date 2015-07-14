#include<stdio.h>
#include<time.h>

int main()
{
	time_t biggest = 0xFFFFFFFF;//why the book says 0x7FFFFFFF

	printf("%s\n",ctime(&biggest));
	return 0;
}
