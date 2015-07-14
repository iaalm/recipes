#include<iostream>
#include<stdio.h>
#include<fstream>

using namespace std;

int N,S,SN;
struct node
{
	int f,t,fn,tn;
};

node * mar;

int w(int n,int from);

int main()
{
	//ifstream cin("in.txt");
	int td,i;
	//cin >> td;
	scanf("%d",&td);
	while(td--)
	{
		//cin >> N;
		scanf("%d",&N);
		S = N;
		mar = new node[N+1];
		for(i = 0;i < N - 1;i++)
			//cin >> mar[i].f >>mar[i].t;
			scanf("%d %d",&mar[i].f,&mar[i].t);
		mar[i].fn = w(mar[0].f,mar[0].t);
		mar[i].tn = w(mar[0].t,mar[0].f);
		cout << SN << " " << S <<endl;
		delete[] mar;
	}
	return 0;
}

int w(int n,int from)
{
	int i,res = 1,s = 0;
	for(i = 0;i < N -1;i++)
	{
		if(mar[i].f == n && mar[i].t != from)
		{
			mar[i].tn = w(mar[i].t,n);
			mar[i].fn = N - mar[i].tn;
			res += mar[i].tn;
			if(mar[i].tn > s)
				s = mar[i].tn;
		}
		else if(mar[i].t == n && mar[i].f != from)
		{
			mar[i].fn = w(mar[i].f,n);
			mar[i].tn = N - mar[i].fn;
			res += mar[i].fn;
			if(mar[i].fn > s)
				s = mar[i].fn;
		}
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
