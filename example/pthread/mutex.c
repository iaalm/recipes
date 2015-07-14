#include<stdio.h>
#include<pthread.h>
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
void* a()
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mymutex);
		for(i = 0;i < 80 ;i++)
			putchar('a');
		pthread_mutex_unlock(&mymutex);
	}
}

void* b()
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mymutex);
		for(i = 0;i < 80 ;i++)
			putchar('b');
		pthread_mutex_unlock(&mymutex);
	}
}

int main()
{
	pthread_t pa,pb;
	pthread_create(&pa,NULL,a,NULL);
	pthread_create(&pb,NULL,b,NULL);
	usleep(10000);
	pthread_cancel(pa);
	pthread_cancel(pb);
	return 0;
}
