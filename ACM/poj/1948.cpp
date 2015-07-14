#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<vector>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<bitset>
#include<map>
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;
int fe[40];
double hsum;
bitset<320010> bt;
int B(int i,int j)
{
	if(i > hsum || j > hsum)
		return 0;
	if(i >= j)
		return (i * (i + 1) / 2 + j + 1);
	else
		return (j * (j + 1) / 2 + i + 1);
}
int main()
{
	int n,i,j,k,sum = 0;
	bt.reset();
	double max = 0,ttt;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin >> fe[i];
		sum += fe[i];
	}
	hsum = sum / 2.0;
	bt[1] = 1;
	for(k = 0;k < n;k++)
		for(i = hsum - 1;i >= 0;i--)
			for(j = i;j >= 0;j--)
				if(bt[B(i,j)])
				{
					bt[B(i + fe[k],j)] = 1;
					bt[B(i,j + fe[k])] = 1;
				}
	for(i = hsum;i >= 0;i--)
	{
		if(hsum * i * ((double)sum - i) * ((double)sum - i) / 4 < max)
				continue;
		for(j = i;j >= 0;j--)
			if(bt[B(i,j)] && (ttt = hsum * (hsum - i) * (hsum - j) * (i + j - hsum)) > max )
				max = ttt;
	}
	if(max != 0)
		cout << (int)(sqrt(max) * 100)<< endl;
	else
		cout << -1 << endl;
	return 0;
}
