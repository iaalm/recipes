#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
using namespace std;

struct devices
{
	int b,p,n;
};
bool sss(devices a,devices b)
{
	return a.b > b.b;
}
int main()
{
	int T,now[210],n,i,j,ii,jj,prize;
	double max;
	devices dev[21000];
	cin >> T;
	while(T--)
	{
		memset(now,-1,sizeof(now));
		n = 0;
		cin >> ii;
		for(i = 0;i < ii;i++)
		{
			cin >> jj;
			for(j = 0;j < jj;j++)
			{
				cin >> dev[n].b >> dev[n].p;
				dev[n].n = i;
				n++;
			}
		}
		sort(dev,dev+n,sss);
		prize = 0;
		for(i =0,jj = 0;jj < ii;i++)
		{
			if(now[dev[i].n] < 0)
			{
				now[dev[i].n] = i;
				prize += dev[i].p;
				jj++;
			}
			else if(dev[now[dev[i].n]].p > dev[i].p)
			{
				prize = prize + dev[i].p - dev[now[dev[i].n]].p;
				now[dev[i].n] = i;
			}
		}
		max = dev[i -1].b / (double) prize;
		for(;i < n;i++)
		{
			if(dev[i].p > dev[now[dev[i].n]].p)
				continue;
			prize = prize + dev[i].p - dev[now[dev[i].n]].p;
			if(dev[i].b / (double)prize > max)
				max = dev[i].b / (double)prize;
			now[dev[i].n] = i;
		}
		cout << fixed << setprecision(3) << max <<endl;
	}
	return 0;
}
