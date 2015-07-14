/**************************************************************
文件名：StrMatch.h
作者：simon
版本：1.0
功能：Rabin-Karp字符串匹配算法简单的技术试验版本
创建日期：2012年6月1日星期五 11:05
修改日期：
备注：
****************************************************************/
#include<stdio.h>
#include<string.h>
#define MOD 97
int StringMatch(const char* str,const char* key)
{
	unsigned int begin,end,kmod = 0,smod = 0,t,i;
	const unsigned int klen = strlen(key),slen = strlen(str);
	if(slen < klen)
		return 0;
	for(begin = 0;begin < klen;begin++)
	{
		kmod <<= sizeof(char) * 8;
		kmod += key[begin];
		kmod %= MOD;
	}
	for(end = 0;end < klen;end++)
	{
		smod <<= sizeof(char) * 8;
		smod += str[end];
		smod %= MOD;
	}
	if(smod == kmod)
	{
		for(i = 0;i < klen;i++)
		{
			if(str[i] != key[i])
				break;
		}
		if(i == klen)
			return 0;
	}
	for(begin = 0;end < slen;begin++,end++)
	{
		smod <<= sizeof(char) * 8;
		smod += str[end];
		smod %= MOD;
		t = str[begin];
		for(i = 0;i < klen;i++)
		{
			t <<= sizeof(char) * 8;
			t %= MOD;
		}
		smod += MOD;
		smod -= t;
		smod %= MOD;
		if(smod == kmod)
		{
			for(i = begin + 1;i <= end;i++)
			{
				if(str[i] != key[i - begin -1])
					break;
			}
			if(i > end)
				return ++begin;
		}
	}
	return -1;
}

int main()
{
	printf("%d\n",StringMatch("123456","56"));
	printf("%d\n",StringMatch("123456","13"));
	printf("%d\n",StringMatch("123456","12"));
	return 0;
}
