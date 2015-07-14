#include<iostream>
#include<queue>
#include<bitset>
using namespace std;

struct node
{
	unsigned short k,n;
};

int main()
{
	bitset<0xFFFF> se;
	queue<node> qu;
	char t;
	unsigned short i;
	const unsigned short cg[16]={51200,58368,29184,12544,35968,20032,10016,4880,2248,1252,626,305,140,78,39,19};
	node j;
	for(i = 0;i < 16;i++)
	{
		cin >> t;
		j.k <<= 1;
		if(t == 'b')
			j.k |= 1;

	}
	j.n = 0;
	if(j.k == 0xFFFF || j.k == 0x0)
	{
		cout <<  j.n << endl;
		return 0;
	}
	qu.push(j);
	se[j.k] = 1;
	while(!qu.empty())
	{
		for(i = 0;i < 16;i++)
		{
			j = qu.front();
			j.k ^= cg[i];
			if(!se[j.k])
			{
				se[j.k] = 1;
				j.n++;
				if(j.k == 0xFFFF || j.k == 0x0)
				{
					cout <<  j.n << endl;
					return 0;
				}
				qu.push(j);
			}
		}
		qu.pop();
	}
	cout << "Impossible" << endl;
	return 0;
}
