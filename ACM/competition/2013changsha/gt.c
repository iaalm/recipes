#include <stdio.h>
int isp(int m){
	int i;
	for(i = 2;i < m;i++)
		if(m % i == 0)
			return 0;
	return 1;
}
int main(int argc, const char *argv[])
{
	int i,j = 0;
	for(i = 2;i <= 80000;i++)
		if(isp(i)){
			j++;
			printf("%d,",i);
	}
	printf("\n%d\n",j);
	return 0;
}
