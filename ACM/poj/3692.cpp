#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,1,sizeof(X))
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
#define INF (1<<26)
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

class Bipartite
{
public:
	int nx,ny,*x,*y;
	list<int> *edge;
	Bipartite(int m,int n)
	{
		nx = m;
		ny = n;
		x = new int[nx];
		memset(x,0xff,nx * sizeof(int));
		y = new int[ny];
		memset(y,0xff,ny * sizeof(int));
		edge = new list<int>[nx];
	}
	//Bipartite(int m):Bipartite(m,m);
	~Bipartite()
	{
		delete[] x;
		delete[] y;
		delete[] edge;
	}
	void addedge(int i,int j)
	{
		edge[i].insert(edge[i].begin(),j);
	}
	int result()
	{
		int *visit = new int[nx],*qu = new int[nx],i,j,k,l,now,result = 0;
		list<int>::iterator it,en;
		for(i = 0;i < nx;i++)
		{
			memset(visit,0xff,nx * sizeof(int));
			now = 1;
			qu[0] = i;
			visit[i] = i;
			for(j = 0;j < now;j++)
			{
				for(it = edge[qu[j]].begin(),en = edge[qu[j]].end();it != en;it++)
				{
					if(y[*it] == -1)
					{
						k = *it;
						for(l = qu[j];l != i;l = visit[l])
						{
							y[k] = l;
							swap(k,x[l]);
						}
						y[k] = i;
						swap(k,x[i]);
						result++;
						goto end;
					}
					k = y[*it];
					if(visit[k] == -1)
					{
						visit[k] = qu[j];
						qu[now++] = k;
					}
				}
			}
end:			;
		}
		delete[] visit;
		delete[] qu;
		return result;
	}
};

int main()
{
	Bipartite* B;
	int N = 0,g,b,m,x,y;
	char tab[200][200];
	while(1)
	{
		clr(tab);
		scanf("%d %d %d",&g,&b,&m);
		if(g == 0)
			return 0;
		B = new Bipartite(g,b);
		while(m--)
		{
			scanf("%d %d",&x,&y);
			tab[x - 1][y - 1] = 0;
		}
		for(x = 0;x < g;x++)
			for(y = 0;y < b;y++)
				if(tab[x][y])
					B->addedge(x,y);
		printf("Case %d: %d\n",++N,g + b - B->result());
		delete B;
	}
}
