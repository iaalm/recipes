#include<iostream>
#include<string>
using namespace std;

struct node
{
	int x,y,z;
	node* p;
};

node *a,*b,*p;

void fl(node*);
void add(int,int,int);

int main()
{
	char map[10][10][10];
	int i,j,k,l,N,x,y,z,res;
	string str;
	while(1)
	{
		res = -1;
		cin >> str >> N;
		if(str != "START")
			break;
		for(i = 0;i < N ;i++)
			for(j = 0;j < N ;j++)
				for(k = 0;k < N ;k++)
					cin >> map[k][j][i];
		cin >> x >> y >> z;
		a = new node;
		a -> x = x;
		a -> y = y;
		a -> z = z;
		a -> p = NULL;
		cin >> x >> y >> z;
		
		l = 1;
		for(i = 0;res == -1 && l;i++)
		{
			l = 0;
			p = a;
			while(p != NULL)
			{
				if(p -> x == x && p -> y == y && p -> z == z)
				{
					l = 1;
					res = i;
					break;
				}
				if(p -> x == -1 || p -> x == N || p -> y == -1 || p -> y == N || p -> z == -1 || p -> z == N || map[p -> x][p -> y][p -> z] == 'X')
				{
					p = p -> p;
					continue;
				}
				l = 1;
				map[p -> x][p -> y][p -> z] = 'X';
				add(p -> x - 1,p -> y,p -> z);
				add(p -> x + 1,p -> y,p -> z);
				add(p -> x,p -> y - 1,p -> z);
				add(p -> x,p -> y + 1,p -> z);
				add(p -> x,p -> y,p -> z - 1);
				add(p -> x,p -> y,p -> z + 1);
				p = p -> p;
			}
			fl(a);
			a = b;
			b = NULL;
		}
		fl(a);
		fl(b);
		if(l == 0)
			cout << "NO ROUTE" << endl;
		else
			cout << N << " " << res << endl;
		cin >> str;
	}
	return 0;
}

void fl(node* p)
{
	node *q;
	while(p != NULL)
	{
		q = p;
		p = p -> p;
		delete q;
	}
}
void add(int x,int y,int z)
{
	node *p = new node;
	p -> x = x;
	p -> y = y;
	p -> z = z;
	p -> p = b;
	b = p;
}
