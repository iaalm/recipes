#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	int pid;
	pid=fork();
	if(pid==-1)
		printf("fork error!\n");
	else if(pid==0)
		printf("child thread!\n");
	else 
		printf("father thread! PID=%d\n",pid);
	getchar();	
	return 0;
}
