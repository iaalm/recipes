//Ctrl-C can kill both thread,but only the orignal thread use the termial.
#include<stdio.h>

int main()
{
	int pid;
	fork();
	//if(fork() != 0)
	//	return 0;
	pid = getpid();
	while(1)
	{
		printf("%d\n",pid);
		sleep(2);
	}
}
