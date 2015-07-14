#include<stdio.h>
#include <ctime>
#include <time.h>

int main()
{
	long ti;
	_time32(&ti);
	printf("%ld\n",ti);
	printf("%ld:%ld:%ld\n",(ti % 86400)/3600+8,(ti % 3600)/60,ti%60);
	return 0;
}
