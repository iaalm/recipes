/**************************************************************
文件名：StringMatch.h
作者：simon
版本：1.0
功能：Rabin-Karp字符串匹配算法
创建日期：2012/05/30 19:16
修改日期：2012/06/06 10:19
备注：下一步可考虑实现C++/string版本
****************************************************************/
#ifndef _STRING_MATCH_RK_
#define _STRING_MATCH_RK_

#include<string.h>

#define MOD 97

char* StringMatch(const char* key,const char* str)
{
	unsigned int begin,end,kmod = 0,smod = 0,t,i;
	const unsigned int klen = strlen(key),slen = strlen(str);
	if(slen < klen)
		return NULL;
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
			return key;
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
				return (key + ++begin);
		}
	}
	return NULL;
}
#endif
