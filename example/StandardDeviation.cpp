/*****************************************
文件名：StandardDeviation.cpp
功能：计算线性分布下（标准差/平均数）的理论值
接口：double StandardDeviation(long n);
版本：1.0
作者：Simon
创建时间：2011/12/06 16:18:22 
更新时间：2011/12/06 16:18:33 
备注：   1计算结果为0.577350
	 2可考虑计算正态分布条件下得理论值
******************************************/

#include <stdio.h>
#include <math.h>

double StandardDeviation(long n);  //计算n情况下相对标准差

double StandardDeviation(long n)
{
	double sd = 0;                 //累加器
        for(long i = 1;i <= n;i++)
        	sd+=(n/2.0-i)*(n/2.0-i)/n;
        sd=sqrt(sd)*2/n;
        return sd;
}

int
main (int argc, char *argv[])
{
	long a=10;
	for(int i=0;i<8;i++)
	{
		printf("10^%d:%10lf\n",i+1,StandardDeviation(a));
		a*=10;
	}
	return 0;
}
