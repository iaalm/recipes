#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<vector>
using namespace std;

int dpt[31][31],nm,li[31];
vector<int> dpv[31][31];
int dp(int lev,int ma,vector<int>& res)
{
	res.clear();
	int &mm = dpt[lev][ma],i,t;
	vector<int> vt;
	if(mm)
	{
		res = dpv[lev][ma];
		return mm;
	}
	if(ma == nm)
		return 0;
	if(lev == li[nm -1])
	{
		res.push_back(lev);
		return (mm = 20 * (lev - li[ma]));
	}
	mm = dp(lev + 1,ma,res) + 4;
	for(i = ma + 1;i < nm;i++)
		if(li[i] > lev)
			break;
	for(;i < nm;i++)
		if(mm > (t = max(dp(lev + 1,i,vt) + 14 , max(lev - li[ma], li[i -1] - lev) * 20)))
		{
			mm = t;
			vt.push_back(lev);
			res = vt;
		}
	dpv[lev][ma] = res;
	return mm;
}

int main()
{
	int i,t,mi;
	vector<int> res,vt;
	while(1)
	{
		cin >> nm;
		if(nm == 0)
			return 0;
		clr(dpt);
		res.clear();
		vt.clear();
		for(i = 0;i < nm;i++)
		{
			cin >> t;
			t--;
			li[i] = t;
		}
		mi = dp(0,0,res);
		for(i = 1;i < nm;i++)
			if(mi > (t = max(dp(0,i,vt) , 20 * li[i - 1])))
			{
				mi = t;
				res = vt;
			}
		cout << mi << endl;
		cout << res.size();
		for(i = res.size() - 1;i >= 0;i--)
			cout << ' ' << res[i] + 1;
		cout << endl;
	}
}
