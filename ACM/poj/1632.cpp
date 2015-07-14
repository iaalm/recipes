#include<iostream>
#include<algorithm>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

struct point
{
	int  x,y;
	bool operator<(const point& a)const
	{
		return (x < a.x || (x == a.x && y < a.y));
	}
} rec[100];

int maxw,N;
long long bx[36],by[36],xx[36],yy[36];
void SS(long long x,long long y,int n,int i);

int main()
{
	int T,i;
	cin >> T;
	while(T--)
	{
		cin >> N;
		maxw = 0;
		clr(bx);
		clr(by);
		clr(xx);
		clr(yy);
		FOR(i,0,N) 
		{
			cin >> rec[i].x >> rec[i].y;
			rec[i].x--;
			rec[i].y--;
			bx[rec[i].y] |= ((long long)1 << rec[i].x);
			by[rec[i].x] |= ((long long)1 << rec[i].y);
			xx[rec[i].x]++;
			yy[rec[i].y]++;
		}
		sort(rec,rec + N,less<point>());
		SS(0,0,0,0);
		cout << maxw << endl;
	}
	return 0;
}

void SS(long long x,long long y,int n,int i)
{
	if(n > maxw)
		maxw = n;
	int mx = 0,my = 0,cx,cy,j;
	while(x >> mx)
		mx++;
	while(y >> my)
		my++;
	FOR(i,i,N - (maxw- n) * (maxw - n))
		if(xx[rec[i].x] > n && yy[rec[i].y] > n && mx <= rec[i].x && my <= rec[i].y)
		{
			cx = 0;
			cy = 0;
			x |= ((long long)1 << rec[i].x);
			y |= ((long long)1 << rec[i].y);
			FOR(j,0,36)
			{
				if((bx[j] & x) == x)
					cx++;
				if((by[j] & y) == y)
					cy++;
			}
			if(cx > n && cy > n)
				SS(x,y,n+1,i+1);
			x &= ~((long long)1 << rec[i].x);
			y &= ~((long long)1 << rec[i].y);

		}
}
