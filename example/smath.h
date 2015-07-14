/*****************************************
文件名：smath.h
功能：个人定义的数学函数库
接口：绝对值： abs(number)        //宏
     平方根：  double sqrt(double number)
     阶乘：    long long fac(short number)
     sin：     double sin(double number)
     cos：     double cos(double number)
     tan：     double tan(double number)
     e^n：     double exp(double number)
     ln：      double ln(double number)
     x^y：     double pow(double number,double degree)
     x^y：     double pow(double number,int degree)   在degre为整数时大约可提高8倍效率；实测10000000次pow(2,20.0)，前者需16s，后者只需2s。
     平均数：  double average(T number[],unsigned long length)
     方差：    double variance(T number[],unsigned long length)
     标准差：  double StandardDeviation(T number[],unsigned long length)
     快速排序：void QuickSort(T arr[],unsigned long long length,bool ascend)
版本：1.0
作者：Simon
创建时间：2011/12/06 16:34:10 
更新时间：2011/12/13 12:13:19   
备注：T为类型模板
******************************************/

#ifndef __SIMON_MATH_H__
#define __SIMON_MATH_H__

#define while(x) while(__builtin_expect(x,1))          //循环一般会进行多次，预测为真，实际上系统自身也如此认为，意义不大

#include <unistd.h>               //使用 void _exit(int states);
#define ERR 0.0000001             //全局误差设置
#define PI 3.1415926545
#define E 2.718282

#define abs(num) num>=0?num:-num          //绝对值宏函数

double sqrt(double number)
{
	if(__builtin_expect(number < 0,0))
		return -1;
	if(__builtin_expect(number == 0,0))
		return 0;
	double pre,next = number/2;
	do
	{
	pre = next;
	next = pre/2+number/pre/2;             //牛顿迭代法 简化式
	}while( abs(pre-next) >= ERR);
	return next;
}

long long fac(short number)                     //阶乘
{
	if(__builtin_expect(number > 1,1))
	{
		long long result = 1;
		do
		{
			result *= number;
			number --;
		}while(number != 1);
	return result;
		
	}
	else
	return 1;
}

double sin(double number)
{
	number -= ((int)(number/2/PI+0.5))*2*PI;         //化到[-PI,PI]
	
	double result = number,item,acc = number;        //acc做累乘器
	number *= number;                                //number作为参数平方（之后只用到参数得平方）
	int n = 3;
	
	do
	{
		acc *= number;
		item = acc;
		item /= fac(n);
		
		if(n%4 == 3)
		{
			item = -item;
		}
		n += 2;
		result += item;
	}while(item > ERR || item < -ERR);
	return result;
}
double cos(double number)
{
	number -= ((int)(number/2/PI+0.5))*2*PI;         //化到[-PI,PI]
	double result = 1,item,acc;                      //acc做累乘器
	number *= number;                                //number作为参数平方（之后只用到参数得平方）
	int n = 2;
	do
	{
		acc *= number;
		
		item /= fac(n);
		
		if(n%4 == 2)
		{
			item = -item;
		}
		n += 2;
		result += item;
	}while(item > ERR || item < -ERR);
	return result;
}

double tan(double number)
{
	double c = cos(number);
	if(__builtin_expect(c != 0,1))
		return sin(number) / c;
	_exit(1);
}

double exp(double number)
{
	double result = 1 + number, item, acc = number;              //acc做累乘器
	int n = 1;
	do
	{
		n++;
		acc *= number;
		item = acc;
		item /= fac(n);
		result += item;
	}while(item > ERR);
	return result;
}

double ln(double number)
{
	if(__builtin_expect(number <= 0,0))                      //错误
		_exit(1);
		
	double result = 0,item = 1,acc = 1;
	while(number > 1)                    //使number<1有利于函数收敛
	{
		number /= E;
		result ++;
	}
	
	number = 1 - number;                 //由于此时number<0恰好抵消符号，故不必讨论符号
	for(int n=1;item > ERR;n++)
	{
		acc *= number;
		item = acc / n;
		result -= item;
	}
	return result;
}

double pow(double number,double degree)
{
	return exp(degree * ln(number));
	
}

double pow(double number,int degree)
{
	double result = number;
	if(degree > 0)
		while(degree != 1)
		{
			result *= number;
			degree --;
		}
	else if(degree != 0)
	{
		return pow(number,-degree);
	}
	else if(number != 0)
		return 1;
	else
		_exit(1);
}

template <typename T>    //模板声明

double average(T number[],unsigned long length)
{
	double average = 0;
	
	for(unsigned int i = 0; i < length; i++)
		average += number[i]/ 1.0 / length;
	
	return average;
}

template <typename T>

double variance(T number[],unsigned long length)
{
	double ave = average(number,length),result = 0;
	
	for(unsigned int i = 0; i < length; i++)
		result += (number[i] - ave) * (number[i] - ave) / length;
		
	return result;
}

template <typename T>

double StandardDeviation(T number[],unsigned long length)
{
	return sqrt(variance(number,length));
}

template <typename T>
void QuickSort(T arr[],unsigned long long length,bool ascend)
{
	if(__builtin_expect(length <= 1,0))
		return ;
	T key = arr[0];
	unsigned long long index = 0,i = 0,j = length - 1;
	do
	{
			
		while((ascend?arr[j] >= key:arr[j] <= key) && j> index)
		{
			j--;
		}
		arr[index] = arr[j];
		index = j;
		                                     //不必真赋值
		
		while((ascend?arr[i] <= key :arr[i] >= key) && i< index)     //防止越界，略显丑陋，但可不赋值
		{
			i++;
		}
		arr[index] = arr[i];
		index = i;
			
	}while(i < j);
	arr[index] = key;                           //此处曾忘记过复原key的值
	QuickSort(arr,index,ascend);
	QuickSort(arr + index + 1,length - index-1,ascend);
}

#endif /* __SIMON_MATH_H__ */

