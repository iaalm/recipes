#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

int N,S,SN;
struct node
{
	int t,n;
};

vector<node> * mar;

int w(int n,int from);

int main()
{
	int td,i,a,b;
	node t;
	cin >> td;
	while(td--)
	{
		cin >> N;
		S = N;
		mar = new vector<node>[N+1];
		for(i = 0;i < N - 1;i++)
		{
			//cin >> a >> b;
			scanf("%d %d",&a,&b);
			t.t = b;
			t.n = 0;
			mar[a].push_back(t);
			t.t = a;
			mar[b].push_back(t);
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
	int res = 1,s = 0;

	for(vector<node>::iterator it = mar[n].begin();it != mar[n].end();it++)
		if(it -> t != from)
		{
			it -> n = w(it -> t,n);
			res += it -> n;
			if(it -> n > s)
				s = it -> n;
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
