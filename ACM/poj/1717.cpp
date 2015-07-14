#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

int s[1000];
int tb[1000][6000];
int dp(int end,int sub)
{
	if(sub == 0)
		return 0;
	if(end * 12 < sub || end * (-12) > sub)
		return 2000;
	if(tb[end][sub])
		return tb[end][sub];
	tb[end][sub] = dp(end - 1,sub);
	if(tb[end][sub] > dp(end -1,sub - 2 * s[end - 1]))
		tb[end][sub] = dp(end -1,sub - 2 * s[end - 1]) + 1;
	return tb[end][sub];
}

int main()
{
	int n,i,a,b,sum = 0;
	cin >> n;
	clr(tb);
	for(i = 0;i < n;i++)
	{
		cin >> a >> b;
		s[i] = a - b;
		sum += s[i];
	}
	for(i = 0;;i++)
	{
		a = dp(n,sum - i);
		b = dp(n,sum + i);
		if(a < 2000 && a <= b)
		{
			cout << a << endl;
			break;
		}
		if(b < 2000 && b < a)
		{
			cout << b << endl;
			break;
		}
	}
	return 0;
}
