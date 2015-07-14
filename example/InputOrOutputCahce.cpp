#include<stdio.h>

int main()
{
	char c;
	while((c=getchar())!='\n')
		putchar(c);//printf("%c",c);相同cout,cerr均相同，结论输入缓冲
	return 0;
}
