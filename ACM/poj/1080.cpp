#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<vector>
#include<bitset>
//#include<fstream>
using namespace std;

const int tran[5][5] = {{5,-1,-2,-1,-3},
		    {-1,5,-3,-2,-4},
		    {-2,-3,5,-2,-2},
		    {-1,-2,-2,5,-1},
		    {-3,-4,-2,-1,0}};
int tb[101][101];
int sa[101],sb[101];
int W(int a,int b)
{
	int i,res = 0;
	if(tb[a][b])
		return tb[a][b];
	if(a == 0)
	{
		for(i = 0;i < b;i++)
			res += tran[4][sb[i]];
	}
	else if(b == 0)
	{
		for(i = 0;i < a;i++)
			res += tran[4][sa[i]];
	}
	else
	{
		res = W(a - 1,b - 1) + tran[sb[b - 1]][sa[a - 1]];
		if((i = W(a - 1,b) + tran[4][sa[a - 1]]) > res)
			res = i;
		if((i = W(a,b - 1) + tran[4][sb[b - 1]]) > res)
			res = i;
	}
	tb[a][b] = res;
	return res;
}

int main()
{
	int T,na,nb,i;
	char t;
	cin >> T;
	while(T--)
	{
		clr(tb);
		cin >> na;
		for(i = 0;i < na;i++)
		{
			cin >> t;
			switch(t)
			{
				case'A':sa[i] = 0;break;
				case'C':sa[i] = 1;break;
				case'G':sa[i] = 2;break;
				case'T':sa[i] = 3;break;
			}
		}
		cin >> nb;
		for(i = 0;i < nb;i++)
		{
			cin >> t;
			switch(t)
			{
				case'A':sb[i] = 0;break;
				case'C':sb[i] = 1;break;
				case'G':sb[i] = 2;break;
				case'T':sb[i] = 3;break;
			}
		}
		cout << W(na,nb) << endl;
	}
	return 0;
}
