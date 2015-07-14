#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<queue>
#define Z(V) cout << #V << ":"<< (V) << endl
using namespace std;


const int Ni = 210;
const int MAX = 1<<26;
struct Edge{
	int u,v,c,f;
	int next;
}edge[Ni*Ni];
int n,m;
int smax[50],us[50];
int edn;//边数
int p[Ni];//父亲
int d[Ni];
int sp,tp;//原点，汇点

void addedge(int u,int v,int c)
{
	edge[edn].u=u; edge[edn].v=v; edge[edn].c=c; edge[edn].f=c;
	edge[edn].next=p[u]; p[u]=edn++;

	edge[edn].u=v; edge[edn].v=u; edge[edn].c=0; edge[edn].f=0;
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
			if(d[u]==-1 && edge[i].c>0 && us[u] < smax[u])
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
			int x=min(smax[u] - us[u],min(edge[i].c,b-r));
			//int x=min(edge[i].c,b-r);
			x=dfs(u,x);
			r+=x;
			edge[i].c-=x;
			edge[i^1].c+=x;
			us[u] += x;
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
	short pp[50][2][10],bl,n,i,j,k;
	scanf("%hd %hd",&bl,&n);
	memset(p,-1,sizeof(p));
	memset(us,0,sizeof(us));
	edn = 0;
	sp = n;
	tp = n + 1;
	smax[sp] = MAX;
	smax[tp] = MAX;
	for(i = 0;i < n;i++)
	{
		scanf("%d",smax + i);
		for(j = 0;j < bl;j++)
			scanf("%hd",&pp[i][0][j]);
		for(j = 0;j < bl;j++)
			scanf("%hd",&pp[i][1][j]);
		for(j = 0;j < i;j++)
		{
			for(k = 0;k < bl;k++)
				if(pp[j][0][k] + pp[i][1][k] == 1)
					break;
			if(k == bl)
				addedge(i,j,min(smax[i],smax[j]));
		}
		for(j = 0;j < i;j++)
		{
			for(k = 0;k < bl;k++)
				if(pp[j][1][k] + pp[i][0][k] == 1)
					break;
			if(k == bl)
				addedge(j,i,min(smax[i],smax[j]));
		}
		for(k = 0;k < bl;k++)
			if(pp[i][0][k] == 1)
				break;
		if(k == bl)
			addedge(sp,i,smax[i]);
		for(k = 0;k < bl;k++)
			if(pp[i][1][k] == 0)
				break;
		if(k == bl)
			addedge(i,tp,smax[i]);
	}
	printf("%d",dinic(sp,tp));
	j = 0;
	for(i = 0;i < edn;i+=2)
		if(edge[i].c != edge[i].f && edge[i].u != sp && edge[i].v != tp)
			j++;
	printf(" %d\n",j);
	for(i = 0;i < edn;i+=2)
		if(edge[i].c != edge[i].f && edge[i].u != sp && edge[i].v != tp)
		{
			printf("%d %d %d\n",edge[i].u + 1,edge[i].v + 1,edge[i].f - edge[i].c);
		}
	//
	return 0;
}
