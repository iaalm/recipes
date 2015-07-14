#include<iostream>
using namespace std;
int set[20][20][20];

int w(int a,int b,int c)
{
	int t;
	if(a <= 0 || b <= 0 || c <= 0)
		return 1;
	if(a > 20 || b > 20 || c > 20)
		return 1048576;
	if(set[a-1][b-1][c-1])
		return set[a-1][b-1][c-1];
	if(a < b&&b < c)
	{
		t = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
		set[a-1][b-1][c-1] = t;
		return t;
	}
	else
	{
		t = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
		set[a-1][b-1][c-1] = t;
		return t;
	}
}

int main()
{
	int a,b,c;
	while(1)
	{
		cin >> a >> b >> c;
		if(a == -1 && b == -1 && c == -1)
			return 0;
		cout <<"w(" << a << ", "  << b << ", " << c << ") = " << w(a,b,c) << endl;
	}
}
