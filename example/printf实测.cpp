/********************************************************
文件名：printf实测.cpp
功能：个测试10s内可执行printf数
接口：无
版本：1.0
作者：Simon
创建时间：2012/04/18 22:06
更新时间：2012/04/18 22:06
备注：windows版本,linux下可直接printf后time
结论:一秒一万条左右,缓冲比不缓冲略快,与执行相比,相当的慢.
******************************************/


#include<stdio.h>
#include<time.h>

int main()
{
	time_t a,b;
	unsigned long i = 0;
	a = time((time_t*) NULL);
	//校准
	do
	{
		b = time((time_t*) NULL);
	}while(b == a);
	//printf("计时开始");
	do
	{
		b = time((time_t*) NULL);
		fprintf(stderr,"\r%d",++i);
	}while(b <= a + 10);
	//printf("\n计时结束");
	putchar(10);
	i = 0;

	//校准
	do
	{
		b = time((time_t*) NULL);
	}while(b == a);
	a = time((time_t*) NULL);
	//printf("计时开始");
	do
	{
		b = time((time_t*) NULL);
		fprintf(stdout,"\r%d",++i);
	}while(b <= a + 10);
	//printf("\n计时结束");
	putchar(10);
	i = 0;

	//校准
	do
	{
		b = time((time_t*) NULL);
	}while(b == a);
	a = time((time_t*) NULL);
	//printf("计时开始");
	do
	{
		b = time((time_t*) NULL);
		i++;
	}while(b <= a + 1);
	fprintf(stderr,"%d\n",i);
	//printf("\n计时结束");
	putchar(10);
	i = 0;
	
	getchar();
	return 0;
}
