#include<stdio.h>

int main()
{
	FILE *fp = fopen("/dev/urandom","rb");
	unsigned long int n;
	read(fp,&n,sizeof(int));
	printf("%ld\n",n);
	return 0;
}
