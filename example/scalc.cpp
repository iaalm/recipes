/********************************
文件名：scalc.cpp
功能：对输入的一个算式进行计算
接口：double sclac(char* expression,long length)
版本：1.0
作者：Simon
创建时间：2011/12/21 19:33:06    
更新时间：2011/12/21 20:32:17  
备注：
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double scalc(char* expression,long length);

double scalc(char* expression,long length)
{
	register char temp;
	double t = 0;
	register int count = 1;
	int i;
	temp = *expression;
	if(temp == '(')
	{
		for(i =1;count > 0;i++)
		{
			if(i > length)
			{
				break;
			}
			switch(*(expression + i))
			{
				case '(': count ++;break;
				case ')': count --;break;
			}
		}
		temp = *(expression + i);
		if(temp == '+')
			return (scalc(expression + 1,i - 2) + scalc(expression + i+1,length- i - 3));
		else if(temp == '-')
			return (scalc(expression + 1,i - 2) - scalc(expression + i+1,length- i - 3));
		if(temp == '*')
			return (scalc(expression + 1,i - 2) * scalc(expression + i+1,length- i - 3));
		else if(temp == '/')
			return (scalc(expression + 1,i - 2) / scalc(expression + i+1,length- i - 3));
		else
			return (scalc(expression + 1,i - 2));
	}
	else if(temp >= '0' && temp <= '9')
	{
		do
		{                                             //取出前操作数
			t *=10;
			t += temp - '0';
			length --;
			expression ++;
			temp = *expression;
		}while(length >= 0 && temp >= '0' && temp <= '9');
		
		if(temp == '+')
			return (t + scalc(expression + 1,length - 1));
		else if(temp == '-')
			return (t - scalc(expression + 1,length - 1));
		if(temp == '*')
			return (t * scalc(expression + 1,length - 1));
		else if(temp == '/')
			return (t / scalc(expression + 1,length - 1));
	}
	else
	{
		exit(1);
	}
}

int main (int argc, char const* argv[])
{
	char str[100];
	gets(str);
	printf("%lf\n",scalc(str,strlen(str)));
	return 0;
}
