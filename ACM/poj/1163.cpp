#include<iostream>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;
int main()
{
	int tr[101][101][2],i,j,n;
	cin >> n;
	FOR(i,0,n)
		FOR(j,0,i + 1)
		{
			cin >> tr[i][j][0];
			tr[i][j][1] = 0;
		}
	tr[0][0][1] = tr[0][0][0];
	FOR(i,1,n)
		FOR(j,0,i)
		{
			if(tr[i][j][1] < tr[i][j][0] + tr[i-1][j][1])
				tr[i][j][1] = tr[i][j][0] + tr[i-1][j][1];
			if(tr[i][j+1][1] < tr[i][j+1][0] + tr[i-1][j][1])
				tr[i][j+1][1] = tr[i][j+1][0] + tr[i-1][j][1];
		}
	j = 0;
	FOR(i,0,n)
		if(tr[n-1][i][1] > j)
			j = tr[n-1][i][1];
	cout << j << endl;
	return 0;
}
