#include<iostream>
#include<string>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

short rec[5100][5100];
string n;

int dp(int from,int to);

int main()
{
	int N,t;
	cin >> N;
	cin >> n;
	t = dp(0,N -1);
	cout << t << endl;
	return 0;
}

int dp(int from,int to)
{
	int min,t;
	if(from >= to)
		return 0;
	if(rec[from][to])
		return rec[from][to];
	if(n[from] == n[to])
		return dp(from + 1,to - 1);
	min = dp(from + 1,to) + 1;
	t = dp(from ,to - 1) + 1;
	if(min > t)
		min = t;
	rec[from][to] = min;
	return min;
}
