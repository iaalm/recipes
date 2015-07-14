#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	int NumOfThread,pid;
	printf("请输入线程数\n");
	scanf("%d",&NumOfThread);
	for(int i=0;i<NumOfThread;i++)
	{
		pid=fork();
		if(pid==-1)
			printf("fork error!\n");
		else if(pid==0)
		{	
			printf("Thread %d\n",i+1);			
			break;
		}
	}	
	return 0;
}
