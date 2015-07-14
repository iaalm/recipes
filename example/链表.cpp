/********************************
文件名：链表
功能：尝试用链表解决问题，耶稣门徒问题
接口：
版本：1.0
作者：Simon
创建时间：2011/12/05 21:38:39   
更新时间：2011/12/05 21:38:43 
备注：
********************************/
#include <stdio.h>

struct lb
{
	int n;
	lb *p;
};

int main (int argc, char const* argv[])
{
	lb a[13];
	for (int i = 0; i < 12; i += 1)
	{
		a[i].n=i+1;
		a[i].p=&a[i+1];
	}
	a[12].n=13;
	a[12].p=&a[0];
	//初始化结束
	int i=1;
	lb *now=&a[0];
	do
	{
		if(i%2==0)
		{
			now->p=(now->p)->p;
		}
		i++;
		now=now->p;
	} while (now!=now->p);
	printf("%d",now->n);
	return 0;
}
