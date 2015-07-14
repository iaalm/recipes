#include<stdio.h>
int main()
{
	char t[1024];
	puts("Content-type: text/html");
	putchar(10);
	puts("<html><body>");
	gets(t);
	puts(t);
	puts("</body></html>");
	return 0;
}
