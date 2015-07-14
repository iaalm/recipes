#include<iostream>
#include<vector>
//#include<fstream>
using namespace std;

int mv[6000][2];
int v[6000];
vector<int> s[6000];
int W(int i,int n)
{
	int min = 0;
	if(mv[i][n] != -1)
		return mv[i][n];
	for(vector<int>::iterator it = s[i].begin();it != s[i].end();it++)
		min += W(*it,1);
	mv[i][n] = min;
	if(n == 1)
	{
		min = v[i];
		for(vector<int>::iterator it = s[i].begin();it != s[i].end();it++)
			min += W(*it,0);
		if(min > mv[i][n])
			mv[i][n] = min;
	}
	return mv[i][n];
}

int main()
{
	int n,i,j;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin >> v[i];
		mv[i][0] = mv[i][1] = -1;
	}

	while(1)
	{
		cin >> i >> j;
		if(i == 0)
			break;
		i--;
		j--;
		s[j].push_back(i);
	}
	for(i = 0,j = 0;i < n;i++)
	{
		if(j < W(i,0))
			j = W(i,0);
		if(j < W(i,1))
			j = W(i,1);
	}
	cout << j << endl;
	return 0;
}
