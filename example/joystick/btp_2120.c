#include<stdio.h>
#include<fcntl.h>

int main()
{
	int fd = open("/dev/hidraw2",O_RDONLY);
	unsigned long long buff;
	while(1){
		read(fd,&buff,8);
		printf("%lX\n",buff);
	}
	return 0;
}
