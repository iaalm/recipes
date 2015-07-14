#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	int pid;
	char *argv[] = {"/"};
	pid=fork();
	if(pid==-1)
		printf("fork error!\n");
	else if(pid==0)
		printf("%d",execvp("ls",argv));
	else 
		printf("father thread! PID=%d\n",pid);
	return 0;
}
