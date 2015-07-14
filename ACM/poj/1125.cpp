#include<iostream>
#include<cstring>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;

int main()
{
	int i,j,k,ft[100][100],N,min,index;
	while(1)
	{
		FOR(i,0,100)
			FOR(j,0,100)
				ft[i][j] = 11000;
		cin >> N;
		if(N == 0)
			break;
		FOR(i,0,N)
		{
			ft[i][i] = 0;
			cin >> j;
			while(j--)
			{
				cin >> k;
				cin >> ft[i][k - 1];
			}
		}
		FOR(k,0,N)
			FOR(i,0,N)
				FOR(j,0,N)
				{
					if(ft[i][j] > ft[i][k] + ft[k][j])
						ft[i][j] = ft[i][k] + ft[k][j];
				}
		min = 11000;
		FOR(i,0,N)
		{
			k = 0;
			FOR(j,0,N)
				if(k < ft[i][j])
					k = ft[i][j];
			if(k < min)
			{
				min = k;
				index = i;
			}
		}
		if(min > 10000)
			cout << "disjoint" << endl;
		else
			cout << index + 1 << " " << min <<endl;
	}
	return 0;
}
