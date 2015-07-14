#include<iostream>
#include<algorithm>
#include<cstring>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;
struct record
{
	int x,y,h;
	bool operator<(const record& a)const
	{
		return h < a.h;
	}
};

int main()
{
	const int setx[4] = { 1,-1, 0, 0},
	      	  sety[4] = { 0, 0, 1,-1};
	int map[100][100],maph[100][100],i,j,W,H,t = 0,x,y,max = 0;
	record l[10000];
	memset(map,0,sizeof(map));
	cin >> H >> W;
	FOR(i,0,H)
		FOR(j,0,W)
		{
			cin >> l[t].h;
			maph[i][j] = l[t].h;
			l[t].x = i;
			l[t].y = j;
			t++;
		}
	sort(l,l+t,less<record>());
	FOR(i,0,t)
		FOR(j,0,4)
		{
			x = l[i].x + setx[j];
			y = l[i].y + sety[j];
			if(x >= 0 && x < H && y >= 0 && y < W && maph[x][y] > l[i].h && map[x][y] <= map[l[i].x][l[i].y])
			{
				map[x][y] = map[l[i].x][l[i].y] + 1;
				if(map[x][y] > max)
					max = map[x][y];
			}
		}
	cout << max + 1 << endl;
	return 0;
}
