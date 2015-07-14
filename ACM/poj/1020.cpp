#include<iostream>
#include<algorithm>
#include<cstring>
#include<bitset>
#define clr(X) memset(X,0,sizeof(X));
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;

int N,list[16],hei[41],side;
bitset<16> used;

bool DFS(int rm);

int main()
{
	int T,i,sum;
	cin >> T;
	while(T--)
	{
		clr(hei);
		used.reset();
		cin >> side>> N ;
		sum = side * side;
		for(i  = 0;i < N;i++)
		{
			cin >> list[i];
			sum -= list[i] * list[i];
		}
		sort(list,list + N,greater<int>());

		if(!sum && DFS(N))
			cout << "KHOOOOB!" << endl;
		else
			cout << "HUTUTU!" << endl;
	}
	return 0;
}

bool DFS(int rm)
{
	int min = side,m_i,i,j;
	if(rm == 0)
		return true;
	FOR(i,0,side)
		if(hei[i] < min)
		{
			m_i = i;
			min = hei[i];
		}
	FOR(i,0,N)
		if(!used[i] && min + list[i] <= side && m_i + list[i] <= side)
		{
			FOR(j,0,list[i])
				if(hei[m_i + j] != min)
					break;
			if(j == list[i])
			{
				FOR(j,0,list[i])
					hei[m_i + j] += list[i];
				used[i] = 1;
				if(DFS(rm - 1))
					return true;
				FOR(j,0,list[i])
					hei[m_i + j] -= list[i];
				used[i] = 0;
				while(i < side && list[i] == list[i + 1])
					i++;
			}
		}
	return false;
}
