#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

struct node
{
	int n;
	node* p;
};
int BFS(int n);
node* list[200];

int main()
{
	int T,i,j,n,m;
	node *p;
	cin >> T;
	while(T--)
	{
		cin >> n;
		clr(list);
		for(i = 0;i < n;i++)
		{
			cin >> j >> j;
			while(j--)
			{
				cin >> m;
				m--;
				p = new node;
				p -> n = m;
				p -> p = list[i];
				list[i] = p;
			}
		}
		cout << BFS(0) << endl;
	}
	return 0;
}

int BFS(int n)
{
	int ll[200];
	node *p;
	int num = 0,max = 1,i;
	for(p = list[n];p != NULL;p = p -> p,num++)
		ll[num] = BFS(p -> n);
	sort(ll,ll+num,less<int>());
	for(i = 0;i < num;i++)
		if(max < ll[i] - i)
				max = ll[i] - i;
	if(num == 0)
		return 1;
	return max + num - 1;
}
