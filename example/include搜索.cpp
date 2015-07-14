/*****************************************
文件名：include搜索.cpp
功能：搜索一个文件中所有的#include<*>
接口：unsigned int search(FILE* fp,char** f,unsigned int length)
版本：1.0
作者：Simon
创建时间：2011/12/28 13:06:14 
更新时间：2011/12/13 12:13:19   
备注：T为类型模板
******************************************/

#include <stdio.h>
#include <string.h>

unsigned int search(FILE* fp,char f[][100],unsigned int length)
{
	unsigned int num=0,i=0;
	const char inc[10] = "#include<";
	char temp[100],t;
	fseek(fp,0,SEEK_SET);
	while((t = getchar()) != -1)
	{printf("%c",t);
		if(t == inc[i])
			i++;
		if(i == 9)
		{
			i = 0;
			while((t = getchar()) != '>')
			{
				temp[i] = t;
				i++;
			}
			temp[i] = '\0';
			printf("%s\n",temp);//strcpy(f[num],temp);
			num++;
			i = 0;
		}
	}
	return num;
}

int main (int argc, char const* argv[])
{
	FILE* fp = fopen("abs.cpp","r");
	char o[100][100];
	unsigned int n = search(fp,o,100);
//	for (unsigned int i = 0; i < n; i += 1)
//	{
//		printf("%s",o[i]);
//	}
	fclose(fp);
	return 0;
}
