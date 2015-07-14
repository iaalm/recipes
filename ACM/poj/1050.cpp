#include<iostream>
#define TNT(X,Y) ((X)*N+(Y))
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;

int main()
{
	int N,i,j,k,l;
	short *map;
	int *val,*p,max = 0;
	cin >> N;
	map = new short[N * N];
	val = new int[N * N];
	FOR(i,0,N)
		FOR(j,0,N)
		{
			cin >> map[TNT(i,j)];
		}
	FOR(k,0,N)
		FOR(i,0,N)
			FOR(j,0,N-k)
			{
				p = val + TNT(i,j);
				if(i != 0 && val[TNT(i - 1,j)] > 0)
					*p = val[TNT(i - 1,j)];
				else
					*p  = 0;
				FOR(l,0,k+1)
					*p += map[TNT(i,j + l)];
				if(*p > max)
					max = *p;
			}
	cout << max << endl;
	return 0;
}
