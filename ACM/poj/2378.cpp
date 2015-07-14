#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int N;

vector<int> * mar,SN;

int w(int n,int from);

int main()
{
	int i,a,b;

	cin >> N;
	mar = new vector<int>[N+1];
	for(i = 0;i < N - 1;i++)
	{
		//cin >> a >> b;
		scanf("%d %d",&a,&b);
		mar[a].push_back(b);
		mar[b].push_back(a);
	}
	w(a,b);
	w(b,a);
	vector<int>::iterator index,it;
	for(i = 0;i < SN.size();i++)
	{
		it = SN.begin();
		for(index = SN.begin();index != SN.end();index++)
			if(*index < *it)
				it = index;
		printf("%d\n",*it);
		*it = N * 2;
	}

	delete[] mar;

	return 0;
}

int w(int n,int from)
{
	int res = 1,s = 0,t;

	for(vector<int>::iterator it = mar[n].begin();it != mar[n].end();it++)
		if(*it != from)
		{
			t = w(*it,n);
			res += t;
			if(t > s)
				s = t;
		}
	if(N - res > s)
		s = N - res;
	if(s <= N / 2)
		SN.push_back(n);
	return res;
}
