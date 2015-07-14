#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

struct device
{
	int b,p;
};

bool gr(device a,device b)
{
	return a.b < b.b;
}

int main()
{
	device dev[100][100];
	int ndev[100],n,T,i,j,max,max_index,min,sum,nprice;
	float best = 0;;
	cin >> T;
	while(T--)
	{
		cin >> n;
		sum = 0;
		max = 0;
		min = 1 << 30;
		nprice = 0;
		for(i = 0;i < n;i++)
		{
			cin >> ndev[i];
			sum += ndev[i];
			for(j = 0;j < ndev[i];j++)
				cin >> dev[i][j].b >> dev[i][j].p;
			sort(dev[i],dev[i] + ndev[i],gr);
			ndev[i]--;
		}
		for(i = 0;i < n;i++)
		{
			nprice += dev[i][ndev[i]].p;
			//min
			if(min > dev[i][ndev[i]].p)
				min = dev[i][ndev[i]].p;
			//init
		}
		best = min / (double)nprice ;
		for(j = 0;j < sum - n/**/;j++)
		{
			//max_index
			max = 0;
			for(i = 0;i < n;i++)
			{
				if(ndev[i] && dev[i][ndev[i]].b > max)
				{
					max_index = i;
					max = dev[i][ndev[i]].b;
				}
			}
			if(dev[max_index][ndev[max_index]].p <= dev[max_index][ndev[max_index] - 1].p)
			{
				ndev[max_index]--;
				continue;
			}
			//get min,nprice,best
			if(dev[max_index][ndev[max_index]].b < min)
				min = dev[max_index][ndev[max_index]].b;
			nprice = nprice - dev[max_index][ndev[max_index]].p + dev[max_index][ndev[max_index] -1].p;
			if(min / nprice > best)
				best = min / nprice;
			ndev[max_index]--;
		}
		cout << fixed << setprecision(3) << best <<endl;
	}	
	return 0;
}
