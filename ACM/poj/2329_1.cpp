#define FOR(I,F,E) for(I = (F);I < (E);I++)
#include<iostream>
using namespace std;

int ma[210][210],acc,s,N;

void check(int x,int y)
{
	if(x >= 0 && x < N && y >= 0 && y < N && ma[x][y] != 0)
	{
		acc++;
		s = ma[x][y];
	}
}

int main()
{
	int i,j,k,p,q;
	cin >> N;
	FOR(i,0,N)
		FOR(j,0,N)
			cin >> ma[i][j];
	FOR(i,0,N)
		FOR(j,0,N)
		{
			if(ma[i][j] != 0)
			{
				cout << ma[i][j];
				if(j == N - 1)
					cout << endl;
				else
					cout << " ";
				continue;
			}
			for(acc = 0,k = 1;!acc;k++)
				for(p = 0;p <= k;p++)
				{
					q = k - p;
					check(i + p,j + q);
					if(q)
						check(i + p,j - q);
					if(p)
						check(i - p,j + q);
					check(i - p,j - q);
					if(acc >= 2)
						break;
				}
			if(acc == 1)
				cout << s;
			else
				cout << 0;
			if(j == N - 1)
				cout << endl;
			else
				cout << " ";
		}
	return 0;
}
