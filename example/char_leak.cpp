#include <stdio.h>

int main()
{
	char a[1]={'a'};
	//char *p=&a;
	printf("%s\n",a-100);
	printf("%d\n",*(a-100));printf("%d\n",*(a-99));printf("%d\n",*(a-98));printf("%d\n",*(a-97));
	printf("%c",300);
	return 0;
}