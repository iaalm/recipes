#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<list>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<bitset>
#include<map>
#include<utility>
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

struct road
{
	int d,l;
};

struct point
{
	int wei,len,ow;
	list<road> edge;
};

int bt[1100];
bool BFS(point* pt,short s,short e)
{
	if(bt[s] != -1)
		return bt[s];
	int t;
	bitset<1100> bs;
	queue<short> qu;
	list<road>::iterator it;
	bs[s] = 1;
	qu.push(s);
	while(!qu.empty())
	{
		s = qu.front();
		qu.pop();
		for(it = pt[s].edge.begin();it != pt[s].edge.end();it++)
		{
			if((t = it->d) == e)
			{
				bt[s] = 1;
				return true;
			}
			if(!bs[t])
			{
				bs[t] = 1;
				qu.push(t);
			}
		}
	}
	bt[s] = 0;
	return false;
}

int main()
{
	int np,ne,sp,tp,i,j,k,l;
	register int m,n;
	point pt[1100];
	road t;
	bool flag;
	list<road>::iterator it,iit;
	queue<int> qu;
	char quq[1100];
	short times[1100];
	while(scanf("%d %d %d %d",&np,&ne,&sp,&tp) != EOF)
	{
		memset(bt,-1,sizeof(bt));
		for(i = 0;i < np;i++)
			pt[i].wei = pt[i].len = pt[i].ow = 1 << 26;
		for(i = 0;i < ne;i++)
		{
			scanf(" %*c%d,%d,%d%*c%d%*c%d%*c",&m,&n,&j,&l,&k);
			if(pt[m].ow > j)
			{
				pt[m].ow = j;
				pt[m].edge.clear();
				t.d = n;
				t.l = l;
				pt[m].edge.insert(pt[m].edge.begin(),t);
			}
			else if(pt[m].ow == j)
			{
				t.d = n;
				t.l = l;
				pt[m].edge.insert(pt[m].edge.begin(),t);
			}
			if(pt[n].ow > k)
			{
				pt[n].ow = k;
				pt[n].edge.clear();
				t.d = m;
				t.l = l;
				pt[n].edge.insert(pt[n].edge.begin(),t);
			}
			else if(pt[n].ow == k)
			{
				t.d = m;
				t.l = l;
				pt[n].edge.insert(pt[n].edge.begin(),t);
			}
		}
		pt[sp].wei = 0;
		pt[sp].len = 0;

		flag = true;
		clr(times);
		clr(quq);
		quq[sp] = 1;
		if(!qu.empty())
			qu.pop();
		qu.push(sp);
		while(!qu.empty())
		{
			i = qu.front();
			qu.pop();
			quq[i] = 0;
			for(it = pt[i].edge.begin();it != pt[i].edge.end();it++)
			{
				k = it -> d;
				if(times[k] <= np && (pt[k].wei > (m = pt[i].wei + pt[i].ow) || (pt[k].wei == m && pt[k].len > pt[i].len + it->l)))
				{
					pt[k].wei = m;
					pt[k].len = pt[i].len + it->l;
					//如果存在超过np重边，会产生问题
					times[k]++;
					if(times[k] == np)
					{
						if(BFS(pt,k,tp))
						{
							flag = false;
							goto end;
						}
						continue;
					}
					if(!quq[k])
					{
						quq[k] = 1;
						qu.push(k);
					}
				}
			}
		}
end:		if(!flag)
		{
			printf("UNBOUND\n");
			continue;
		}
		if(pt[tp].wei == 1 << 26)
			printf("VOID\n");
		else
			printf("%d %d\n",pt[tp].wei,pt[tp].len);

	}
	return 0;
}
