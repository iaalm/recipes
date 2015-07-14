#include<stdio.h>
#include<pthread.h>

void* a()
{
	while(1)
		putchar('a');
}

void* b()
{
	while(1)
		putchar('b');
}

int main()
{
	pthread_t pa,pb;
	pthread_create(&pa,NULL,a,NULL);
	pthread_create(&pb,NULL,b,NULL);
	usleep(10000);
	pthread_cancel(pa);
	pthread_join(pa,NULL);
	pthread_cancel(pb);
	pthread_join(pb,NULL);
	return 0;
}
