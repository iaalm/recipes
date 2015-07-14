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
#define INF (1<<26)
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

struct aaa
{
	int i,n;
};
struct node
{
	int p,b,s,n;
	char name[70];
	list<aaa> j;
};

int bcj[30010];
int visited[30010];
node name[30010];
int res[30010][2];

void L(int i,int dot)
{
	int n;
	for(n = 0;n < dot;n++)
		putchar('.');
	puts(name[i].name);
	dot++;
	for(i = name[i].s;i != -1;i = name[i].b)
		L(i,dot);
}

int find(int i)
{
	return bcj[i] == -1?i:bcj[i] = find(bcj[i]);
}

void LCA(int n)
{
	int i;
	list<aaa>::iterator it,en;
	i = name[n].s;
	visited[n] = 1;
	while(i != -1)
	{
		LCA(i);
		bcj[i] = n;
		i = name[i].b;
	}
	for(it = name[n].j.begin(),en = name[n].j.end();it != en;it++)
		if(visited[it->i])
		{
			res[it->n][0] = 2;
			res[it->n][1] = find(it->i);
		}
}

int main()
{
	freopen("in.txt","r",stdin);
	map<string,int> stree;
	aaa at;
	char ts[70],tss[70],ttt[20];
	int accc[70],*p;
	int now,n,i,j,k;
	while(1)
	{
		scanf("%d",&n);
		if(n == 0)
			return 0;
		
		stree.clear();
		scanf("%s",name[0].name);
		name[0].p = name[0].b = name[0].s = -1;
		name[0].n = 0;
		accc[0] = 0;
		name[0].j.clear();
		for(now = 1;now < n;now++)
		{
			scanf("%s",ts);
			for(i = 0;ts[i] == '.';i++);
			accc[i] = now;
			strcpy(name[now].name,ts + i);
			stree.insert(make_pair<string,int>(string(name[now].name),now));
			name[now].j.clear();
			i--;
			name[now].s = -1;
			name[now].n = 0;
			name[now].p = accc[i];
			name[accc[i]].n++;
			p = &(name[accc[i]].s);
			while(1)
			{
				if(*p == -1 || strcmp(name[*p].name,name[now].name) > 0)
				{
					name[now].b = *p;
					*p = now;
					break;
				}
				p = &(name[*p].b);
			}
		}
		puts("a");
		scanf("%d",&now);
		for(i = 0;i < now;i++)
		{
			scanf("%s",ttt);
			switch(ttt[0])
			{
				case'L':
					res[i][0] = 0;
					break;
				case'b':
					scanf("%s",ts);
					res[i][0] = 1;
					res[i][1] = name[name[(stree.find(string(ts)))->second].p].n;
					break;
				case'c':
					scanf("%s%s",ts,tss);
					j = stree.find(string(ts))->second;
					k = stree.find(string(tss))->second;
					at.n = i;
					at.i = k;
					name[j].j.insert(name[j].j.begin(),at);
					at.i = j;
					name[k].j.insert(name[k].j.begin(),at);
					res[i][0] = 3;
					break;
			}
		}
		memset(bcj,-1,sizeof(bcj));
		clr(visited);
		LCA(0);
		for(i = 0;i < now;i++)
		{
			switch(res[i][0])
			{
				case 0:
					L(0,0);
					break;
				case 1:
					printf("%d\n",res[i][1]);
					break;
				case 2:
					puts(name[res[i][1]].name);
					break;
			}
		}

	}
}
