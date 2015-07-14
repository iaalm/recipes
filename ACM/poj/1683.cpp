#include<iostream>
#include<cstring>
#define FOR(I,F,E) for(I=F;I<E;I++)
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

char res[7][7][7][7];		//kind num
int s[7][7];			//man kind
int M,N;

bool DFS(int n,int m)            //kind num
{
	int i,j,flag[7];
	if(n == N)
		return true;
	if(m == M)
		return DFS(n+1,0);
	FOR(i,0,M)
	{
		flag[i] = 0;
		FOR(j,0,n)
		{
			if(res[j][s[i][j]-1][n][m] == 'R')
			{
				if(flag[i] == 2)
					return false;
				else
					flag[i] = 1;
			}
			else if(res[j][s[i][j]-1][n][m] == 'N')
			{
				if(flag[i] == 1)
					return false;
				else
					flag[i] = 2;
			}
		}
	}
	FOR(i,0,M)
		if(flag[i] == 1)
		{
			if(s[i][n])
				return false;
			else
			{
				s[i][n] = m+1;
				flag[i] = DFS(n,m+1);
				if(!flag[i])
					s[i][n] = 0;
				return flag[i];
			}
		}
	FOR(i,0,M)
		if(flag[i] != 2 && !s[i][n])
		{
			s[i][n] = m+1;
			if(DFS(n,m+1))
				return true;
			s[i][n] = 0;
		}
	return false;
}

int main()
{
	int T,i,j,k,l;
	char character[7][7],t;
	cin >> T;
	while(T--)
	{
		cin >> N >> M;
		clr(res);
		clr(s);
		FOR(i,0,N)
			FOR(j,0,M)
				cin >> character[i][j];
		while(1)
		{
			cin >> i >> j >> t >> k >> l;
			if(i == 0 && j == 0 && k == 0 && l == 0)
				break;
			i--;
			j--;
			k--;
			l--;
			res[i][j][k][l] = t;
			res[k][l][i][j] = t;

		}
		FOR(i,0,M)
			s[i][0] = i+1;
		DFS(1,0);
		FOR(i,0,M)
		{
			FOR(j,0,N)
				cout << character[j][s[i][j]-1];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
