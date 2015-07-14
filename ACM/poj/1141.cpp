#include<iostream>
#include<string>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

int rec[200][200];
string n;

int dp(int from,int to);
void re(int from,int to,int n,string &str);
int main()
{
	string f;
	int res;
	cin >> n;
	clr(rec);
	res = dp(0,n.size() - 1);
	re(0,n.size() - 1,res,f);
	cout << f << endl;
	return 0;
}

int dp(int from,int to)
{
	int min = 10000,i,j;
	if(from > to)
		return 0;
	if(from == to)
		return 2;
	if(rec[from][to] != 0)
		return rec[from][to];
	if((n[from] == '(' && n[to] == ')' )||(n[from] == '[' && n[to] == ']' ))
		min = 2 + dp(from + 1,to - 1);
	for(i = from;i < to;i++)
	{
		j = dp(from,i) + dp(i + 1,to);
		if(j < min)
			min = j;
	}
	rec[from][to] = min;
	return min;
}
void re(int from,int to,int num,string &str)
{
	string s;
	int i,j;
	if(from == to)
	{
		if(n[from] == '(' || n[from] == ')')
			str = "()";
		else
			str = "[]";
		return;
	}
	if(from > to)
	{
		str = "";
		return;
	}
	if(n[from] == '(' && n[to] == ')' && num - 2 == dp(from + 1,to - 1))
	{
		re(from + 1,to - 1,num - 2,s);
		str = '(' + s + ')';
		return;
	}
	if(n[from] == '[' && n[to] == ']' && num - 2 == dp(from + 1,to - 1))
	{
		re(from + 1,to - 1,num - 2,s);
		str = '[' + s + ']';
		return;
	}
	for(i = from;i < to;i++)
	{
		j = dp(from,i);
		if(j + dp(i + 1,to) == num)
		{
			re(from,i,j,str);
			re(i + 1,to,num - j,s);
			str += s;
			return;
		}
	}
}
