#include<stdio.h>
#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<queue>
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;
const int Ni = 450;
const int MAX = 1<<26;
struct Edge{
	int u,v,c;
	int next;
}edge[90*Ni];
int n,m;
int edn;//边数
int p[Ni];//父亲
int d[Ni];
int sp,tp;//原点，汇点

void addedge(int u,int v,int c)
{
	edge[edn].u=u; edge[edn].v=v; edge[edn].c=c;
	edge[edn].next=p[u]; p[u]=edn++;

	edge[edn].u=v; edge[edn].v=u; edge[edn].c=0;
	edge[edn].next=p[v]; p[v]=edn++;
}
int bfs()
{
	queue <int> q;
	memset(d,-1,sizeof(d));
	d[sp]=0;
	q.push(sp);
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		for(int i=p[cur];i!=-1;i=edge[i].next)
		{
			int u=edge[i].v;
			if(d[u]==-1 && edge[i].c>0)
			{
				d[u]=d[cur]+1;
				q.push(u);
			}
		}
	}
	return d[tp] != -1;
}
int dfs(int a,int b)
{
	int r=0;
	if(a==tp)return b;
	for(int i=p[a];i!=-1 && r<b;i=edge[i].next)
	{
		int u=edge[i].v;
		if(edge[i].c>0 && d[u]==d[a]+1)
		{
			int x=min(edge[i].c,b-r);
			x=dfs(u,x);
			r+=x;
			edge[i].c-=x;
			edge[i^1].c+=x;
		}
	}
	if(!r)d[a]=-2;
	return r;
}

int dinic(int sp,int tp)
{
	int total=0,t;
	while(bfs())
	{
		while((t=dfs(sp,MAX)))
			total+=t;
	}
	return total;
}

int main()
{
	int i,j,k,q[7],d,w,T,nf,maxw,acc;
	scanf("%d",&T);
	sp= 98;
	tp = 99;
	while(T--)
	{
		maxw = 0;
		acc = 0;
		edn = 0;
		memset(p,-1,sizeof(p));
		scanf("%d",&nf);
		for(i = 0;i < nf;i++)
		{
			for(j = 0;j < 7;j++)
				scanf("%d",q + j);
			scanf("%d %d",&d,&w);
			if(w > maxw)
				maxw = w;
			acc += d;
			addedge(sp,i,d);
			for(j = 0;j < 7;j++)
			{
				if(!q[j])
					continue;
				for(k = 0;k < w;k++)
					addedge(i,100 + j + k * 7,1);
			}

		}
		j = maxw * 7 + 100;
		for(i = 100;i < j;i++)
			addedge(i,tp,1);
		if(dinic(sp,tp) == acc)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
