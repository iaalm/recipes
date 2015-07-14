#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int choosex[4] = {0,1,0,1},
      	  choosey[4] = {0,0,1,1};

struct sqr
{
	int x,y,l;
};

sqr list[20];
int N,S;

bool sss(sqr a,sqr b)
{
	return a.l > b.l;
}

bool DFS(int no);
int check(int no);

int main()
{
	int T,i,j;
	cin >> T;
	while(T--)
	{
		cin >> S;
		cin >> N;
		memset(list,0,sizeof(list));
		j = S * S;
		for(i = 0;i < N;i++)
		{
			cin >> list[i].l;
			j -= list[i].l * list[i].l;
		}
		sort(list,list + N,sss);
		list[0].x = list[0].y = 0;
		if(!j && DFS(1))
			cout << "KHOOOOB!" << endl;
		else
			cout << "HUTUTU!" << endl;

	}
	return 0;
}

bool DFS(int no)
{
	int i,j,t;
	register sqr* const p = list + no;
	if(no >= N)
		return true;
	t = p -> l;
	for(i = 0;i < S - p -> l + 1;i++)
		for(j = 0;j < S - p -> l + 1;)
		{
			p -> x = i;
			p -> y = j;
			if(!(t = check(no)))
			{
				if(DFS(no + 1))
					return true;
				j++;
			}
			else
				j += t;
		}
	return false;
}

int check(int no)
{
	int max = 0,i,x,y;
	register sqr* const p = list + no;
	register sqr *q = list;
	while(p != q)
	{
		for(i = 0;i < 4;i++)
		{
			x = p -> x + p -> l * choosex[i];
			y = p -> y + p -> l * choosey[i];
			if(x >= q -> x && x < q -> x + q -> l && y >= q -> y && y < q -> y + q -> l)
			{
				if(max < q -> l + q -> y - p -> y)
					max = q -> l + q -> y - p-> y;
				break;
			}
		}
		q++;
	}
	return max;
}
