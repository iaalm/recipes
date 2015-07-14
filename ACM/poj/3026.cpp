#include<stdio.h>
#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<vector>
#include<queue>
using namespace std;

struct node
{
	int len,x,y;
	bool operator>(const node& n)const
	{
		return len > n.len;
	}
};

int main()
{
	const int setx[4] = { 1,-1, 0, 0},
	      	  sety[4] = { 0, 0, 1,-1};
	int w,h,T,A,i,j,mi,tm[51][51];
	node t;
	char map[50][70];
	priority_queue<node,vector<node>,greater<node> > pq;
	scanf("%d",&T);
	while(T--)
	{
		clr(tm);
		A = 0;
		t.len = 0;
		mi = 0;
		while(!pq.empty())
			pq.pop();
		scanf("%d%d",&w,&h);
		gets(map[0]);
		for(i = 0;i < h;i++)
		{
			gets(map[i]);
			for(j = 0;j < w;j++)
			{
				if(map[i][j] == 'A')
					A++;
				if(map[i][j] == 'S')
				{
					map[i][j] = '#';
					t.x = i;
					t.y = j;
				}
			}
		}
		pq.push(t);
		while(A)
		{
			for(i = 0;i < 4;i++)
			{
				t = pq.top();
				t.x += setx[i];
				t.y += sety[i];
				switch(map[t.x][t.y])
				{
					case '#':
						continue;
					case 'A':
						A--;
						mi += (t.len + 1);
						t.len = 0;
						pq.push(t);
						i = -1;
						map[t.x][t.y] = '#';
						break;
					case ' ':
						if(tm[t.x][t.y] != 0 && tm[t.x][t.y] <= t.len + 1)
							continue;
						t.len++;
						pq.push(t);
						break;
				}
				tm[t.x][t.y] = t.len;
			}
			pq.pop();
		}
		printf("%d\n",mi);
	}
	return 0;
}
