#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<vector>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<bitset>
#include<map>
#include<utility>
#include<cmath>
#define INF (1<<26)
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

float tab[2000][2000];
struct st
{
	int x,y;
	float min;
};

int main()
{
	int num = 0,n,i,j;
	st s[2000];
	queue<int> qu;
	while(1)
	{
		scanf("%d",&n);
		if(n == 0)
			return 0;
		for(i = 0;i < n;i++)
		{
			scanf("%d %d",&s[i].x,&s[i].y);
			s[i].min = INF;
			for(j = i - 1;j >= 0;j--)
				tab[i][j] = tab[j][i] = sqrt((float)((s[i].x - s[j].x) * (s[i].x - s[j].x) + (s[i].y - s[j].y) * (s[i].y - s[j].y)));
		}
		s[0].min = 0;
		qu.push(0);
		while(!qu.empty())
		{
			j = qu.front();
			qu.pop();
			for(i = 0;i < n;i++)
				if(s[i].min > max(s[j].min , tab[i][j]))
				{
					s[i].min = max(s[j].min , tab[i][j]);
					qu.push(i);
				}
		}
		printf("Scenario #%d\nFrog Distance = %.3f\n\n",++num,s[1].min);
	}
}
