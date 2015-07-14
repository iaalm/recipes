#include <stdio.h>
#include <stdlib.h>

double average(double number[],unsigned long long length);
double variance(double number[],unsigned long long length);
double sqrt(double number);

double average(double number[],unsigned long long length)
{
	double average = 0;
	
	for(unsigned int i = 0; i < length; i++)
		average += number[i]/ 1.0 / length;
	
	return average;
}

double variance(double number[],unsigned long long length)
{
	double ave = average(number,length),result = 0;
	
	for(unsigned int i = 0; i < length; i++)
		result += (number[i] - ave) * (number[i] - ave) / length;
		
	return result;
}

double sqrt(double number)
{
	double pre,next = number/2;
	do
	{
	pre = next;
	next = pre/2+number/pre/2;printf("%lf %lf\n",pre,next);             //牛顿迭代法 简化式
	}while(pre - next >= 1e-5 || next - pre >= 1e-5 );
	return next;
}

int main()
{
	unsigned long long n;
	printf("请输入数据个数：");
	scanf("%lld",&n);
	double *p = (double*) malloc (n * sizeof(double)),v;
	for(unsigned long long i = 0;i < n; i++)
	{
		printf("请输入第%lld个数：",i+1);
		scanf("%lf",p+i);
	}
	
	printf("平均值：%lf\n",average(p,n));
	printf("方差：%lf\n",v = variance(p,n));
	printf("标准差：%lf\n按任意键退出\n",sqrt(v));
	getchar();getchar();getchar();
	return 0;
}
