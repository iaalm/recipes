#include<iostream>
#include<bitset>
using namespace std;

void add(bitset<2100>& a,const bitset<2100>& b,int bn,int wy)
{
	while(bn--)
	{
		a[bn + wy] = a[bn + wy] ^ b[bn];
	}
}

int main()
{
	int T,i,fn,gn,hn,mn,t;
	bitset<2100> f,g,h,m;
	cin >> T;
	while(T--)
	{
		cin >> fn;
		m.reset();
		for(i = fn - 1;i >= 0;i--)
		{
			cin >> t;
			f[i] = t;
		}
		cin >> gn;
		for(i = gn - 1;i >= 0;i--)
		{
			cin >> t;
			g[i] = t;
		}
		cin >> hn;
		for(i = hn - 1;i >= 0;i--)
		{
			cin >> t;
			h[i] = t;
		}
		for(i = 0;i < fn;i++)
			if(f[i])
				add(m,g,gn,i);
		for(i = 2100 - 1;i >= hn - 1;i--)
			if(m[i])
				add(m,h,hn,i - hn + 1);
		mn = 2100;
		while(mn != 0 && !m[mn - 1])
			mn--;
		cout << mn;
		if(mn == 0)
			cout << " " << 0;
		for(i = mn -1;i >= 0;i--)
			cout << " " << m[i];
		cout << endl;
	}
	return 0;
}
