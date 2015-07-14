#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<utility>
#include<set>
#include<queue>
#include<bitset>
//#include<fstream>
using namespace std;

struct task
{
	int n,size;
	vector<int> se;
};

struct cmp
{
	bool operator()(const task tt,const task& t)const
	{
		if(tt.n < t.n)
			return true;
		if(tt.n > t.n)
			return false;
		if(tt.se < t.se)
			return true;
		if(tt.se > t.se)
			return false;
		return false;
	}
};

bool inr(set<task,cmp> &se,task ta,int i,int n)
{
	pair<set<task>::iterator,bool> t;
	ta.n += n;
	ta.se.push_back(i);
	t = se.insert(ta);
	return t.second;
}

bool fi(vector<int> se,int i)
{
	vector<int>::iterator it;
	for(it = se.begin();it != se.end();it++)
		if(*it == i)
			return false;
	return true;
}

int main()
{
	int nv,nr,begin,end,max,i,j,ccc = 0;
	bool flag;
	queue<int> q;
	int map[20][20];
	set<task,cmp> vt[20];
	set<task,cmp>::iterator it;
	task ttt;
	while(1)
	{
		ccc++;
		cin >> nv;
		if(nv == -1)
			return 0;
		while(!q.empty())
			q.pop();
		clr(map);
		for(i = 0;i < 20;i++)
			vt[i].clear();
		cin >> nr;
		for(i = 0;i < nr;i++)
		{
			cin >> begin >> end >> j;
			begin--;
			end--;
			map[begin][end] = map[end][begin] = j;
		}

		cin >> begin >> end >> max;
		begin--;
		end--;
		q.push(begin);
		ttt.n = 0;
		ttt.se.clear();
		ttt.se.push_back(begin);
		vt[begin].insert(ttt);
		while(!q.empty())
		{
			i = q.front();
			for(j = 0;j < nv;j++)
				if(map[i][j])
				{
					flag = false;
					for(it = vt[i].begin();it != vt[i].end();it++)
					{
						if(fi(it->se,j) && it->n + map[i][j] <= max && inr(vt[j],*it,j,map[i][j]))
							flag = true;
					}
					if(flag)
						q.push(j);
				}
			q.pop();
		}
		cout << "Case " << ccc << ':' << endl;
		if(vt[end].size() == 0)
			cout<< " NO ACCEPTABLE TOURS" << endl;
		else
			for(it = vt[end].begin();it != vt[end].end();it++)
			{
				cout << ' ' << it->n << ':';
				for(i = 0;i < it->se.size();i++)
						cout << ' ' << it->se[i] + 1;
				cout << endl;
			}
		cout << endl;
	}
}
