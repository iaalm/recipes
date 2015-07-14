#include <stdio.h>

int main()
{
	char *str="add";
	printf("%X\n",str);
	printf("%X\n",str+3);
	*(str+2)='a';   //被保护不能为written
	//*(str+10)='\0';
	printf("%s\n",*str);
}