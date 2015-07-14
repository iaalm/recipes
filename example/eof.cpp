/*****************************************
文件名：eof.cpp
功能：测试读到文件末尾后继续读取的结果
接口：无
版本：1.0
作者：Simon
创建时间：2012/04/21 10:02
更新时间：2012/04/21 10:02
备注：   不论二进制或普通状态下,都不对变量的值作任何改变
******************************************/

#include<stdio.h>

int main()
{
	int i;
	char t;
	FILE *fp = fopen("eof.txt","r");
	for(i = 0;i < 10;i++)
	{
	        fscanf(fp,"%c",&t);
	        printf("%c",t);
	}
	t = '1';
	fread(&t,1,1,fp);
	printf("%c\n",t);
	
	fclose(fp);
	
	fp = fopen("eof.txt","rb");
	for(i = 0;i < 10;i++)
	{
	        fread(&t,1,1,fp);
	        printf("%c",t);
	}
	t = '1';
	fread(&t,1,1,fp);
	printf("%c",t);
	
	getchar();
	fclose(fp);
	
	return 0;
}
