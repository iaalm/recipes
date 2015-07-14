#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd;
	fd = open("echo.c",O_RDONLY);
	dup2(fd,0);
	/*
	freopen("a.c","r",stdin);	//it's ok too.
	*/

	//putchar(getchar());		//can not use it again
	//putchar(10);
	
	execlp("cat","cat",0);

	return 0;
}
