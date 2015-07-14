#include <stdio.h>
#include <iostream>
#include <string.h>
#define N 1005
#define M 1001005
#define MIN(a,b) ((a)<(b)?(a):(b))
struct Node {
	int j, tag, id;
	Node *next;
};
int m, n, wei[M], minV;
int nid;
Node *e[N];
int bridgeNum, bridge[M];
int low[N], dfn[N];
int visited[N];

int addEdge(Node *e[], int i, int j) {
	Node *p;
	for(p=e[i]; p!=NULL; p = p->next) {
		if(p->j==j) break;
	}
	if(p != NULL) {
		p->tag++;
		return 0;
	}
	p = new Node();
	p->j = j;
	p->next = e[i];
	e[i] = p;
	p->id=nid;
	p->tag = 0;
	return 1;
}

void dfs(int i, int father, int dth) {
	visited[i] = 1;
	dfn[i] = low[i] = dth;
	Node *p;
	for(p=e[i];p!=NULL;p=p->next) {
		int j=p->j;
		if(j!=father && visited[j]==1) {
			low[i]=MIN(low[i], dfn[j]);
		}
		if(visited[j]==0) {
			dfs(j, i, dth+1);
			low[i]=MIN(low[i], low[j]);
			if(low[j]>dfn[i]&&!p->tag)
//			if(low[j]>dfn[i])
				bridge[p->id]=++bridgeNum;
		}
	}
	visited[i]=2;
}

int main() {
	freopen("in.txt", "r", stdin);
	int u, v, w;
	int counts=0;
	while(~scanf("%d%d", &n, &m)) {
		if(m==0 && n==0) break;
		nid=0;
		memset(e, 0, sizeof(Node*)*N);
		for(int i = 0; i < m; i++,nid++) {
			scanf("%d%d%d", &u, &v, &w);
			addEdge(e,u-1,v-1);
			addEdge(e,v-1,u-1);
			bridge[nid]=0;
			wei[nid]=w;
		}
		bridgeNum=0;
		memset(visited, 0, sizeof(int)*N);
		memset(bridge, 0, sizeof(int)*m);
		memset(low,0,sizeof(int)*N);
		memset(dfn, 0, sizeof(int)*N);
		dfs(0, -1, 1);
		counts=0;
		for(int i = 0; i < n; i++) {
			if(visited[i]) counts++;
		}
		if(counts<n) {
			printf("0\n");
			continue;
		}
		minV = 0x3f3f3f3f;
		for(int i = 0; i < m; i++) {
			if(bridge[i]) {
				if(wei[i]<minV) {
					minV = wei[i];
				}
			}
		}
		if(minV==0) minV=1;
		if(minV==0x3f3f3f3f) printf("-1\n");
		else printf("%d\n", minV);
	}
	return 0;
}
