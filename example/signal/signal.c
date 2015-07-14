#include<signal.h>
#include<stdio.h>

void stopsign()
{
	printf("SIGTSTP\n");
}

int main()
{
	signal(SIGTSTP,stopsign);
	while(1);
	return 0;
}
