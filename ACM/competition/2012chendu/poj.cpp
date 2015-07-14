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

struct node
{
	char n,y;
};
int main()
{
	//freopen("in.txt","r",stdin);
	char n[20],have[10];
	list<char> res;
	list<char> :: iterator it;
	int N,base,i,len,count,acc;
	while(scanf("%d %d",&N,&base) != EOF)
	{
		res.clear();
		clr(have);
		count = 0;
		for(i = 0;N;i++)
		{
			n[i] = N % base;
			res.insert(res.end(),n[i]);
			if(!have[n[i]])
			{
				have[n[i]] = 1;
				count ++;
			}
			N /= base;
		}
		len = i;
		while(1)
		{
			if(count <= 2)
				break;
			acc = 0;
			for(i = 0,it = res.begin();i < len || acc;it++,i++)
			{
				if(it == res.end())
				{
					it = res.insert(it,0);
					have[0]++;
				}
				have[*it]--;
				if(!have[*it])
					count--;
				*it += acc;
				if(i < len)
					*it += n[i];
				acc = *it / base;
				*it %= base;
				if(!have[*it])
					count ++;
				have[*it]++;
			}
		}
		if(count == 2)
		{
		}
		it = res.end();
		while(res.begin() != --it)
			printf("%d",*it);
		printf("%d\n",*it);
	}
	return 0;
}
