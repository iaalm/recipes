#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int N,S,SN;

vector<int> * mar;

int w(int n,int from);

int main()
{
	int td,i,a,b;
	cin >> td;
	while(td--)
	{
		cin >> N;
		S = N;
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
		cout << SN << " " << S <<endl;
		delete[] mar;
	}
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
	if(s < S||(s == S && n < SN))
	{
		S = s;
		SN = n;
	}
	return res;
}
