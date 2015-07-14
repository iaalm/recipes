#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<vector>
#include<queue>
using namespace std;

const char arb[4] = {'T','G','C','A'};
char *se;
int n;

struct node
{
	char res[61];
	vector<int>* tab;
};

int main()
{
	int i,j,k,T;
	char rrr[70];
	queue<node> que;
	vector<int>::iterator be,en;
	node t;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		rrr[0] = '\0';
		se = (char*) malloc (n * 64 * sizeof(char));
		t.tab = new vector<int>[n];
		for(i = 0;i < n;i++)
			scanf("%s",se + 64 * i);
		for(i = 0;i < 4;i++)
		{
			t.res[0] = arb[i];
			t.res[1] = '\0';
			for(j = 0;j < n;j++)
				t.tab = new vector<int>[n];
			for(j = 0;j < n;j++)
				for(k = 0;k < 60;k++)
					if(arb[i] == se[j * 64 + k])
						t.tab[j].push_back(k + 1);
			que.push(t);
		}
		while(!que.empty())
		{
			for(i = 0;i < 4;i++)
			{
				strcpy(t.res,que.front().res);
				j = strlen(t.res);
				t.res[j++] = arb[i];
				t.res[j] = '\0';
				for(j = 0;j < n;j++)
					t.tab = new vector<int>[n];
				for(j = 0;j < n;j++)
				{
					k = 0;
					for(be = que.front().tab[j].begin(),en = que.front().tab[j].end();be != en;be++)
						if(*be != 60 && arb[i] == se[j * 64 + *be])
						{
							t.tab[j].push_back(*be + 1);
							k = 1;
						}
					if(!k)
						break;
				}
				if(j == n)
				{
					que.push(t);
					strcpy(rrr,t.res);
				}
			}
			delete[] que.front().tab;
			que.pop();
		}
		free(se);
		delete[] t.tab;
		if(strlen(rrr) < 3)
			puts("no significant commonalities");
		else
			puts(rrr);
	}
	return 0;
}
