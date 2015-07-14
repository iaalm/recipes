/*
ID: simonin1
LANG: C++
TASK:humble
*/

#include<fstream>
#include<bitset>

using namespace std;

struct node
{
	unsigned int num;
	bitset<100> set;
};

int gk,gn,*gp;
node *res;
unsigned int getNext(int n);

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	int i;
	in >> gk >> gn;
	gp = new int[gk];
	for(i = 0;i < gk;i++)
	        in >> gp[i];
	res = new node[gn];
	res[0].num = 1;
	res[0].set.reset();
	for(i = 1;i < gn;i++)
	{
		res[i].num = getNext(i);
		res[i].set.reset();
	}
	out << getNext(gn) << endl;
	return 0;
}

unsigned int getNext(int n)
{
	unsigned int min = 0 - 1,max = res[n - 1].num,t,ii,jj;
	int i,j;
	for(i = 0;i < gk;i++)
		for(j = n - 1;j >= 0;j--)
		{
			if(res[j].set[i] == 1)
				continue;
			t = res[j].num * gp[i];
			if(t <= max)
				break;
			if(t < min)
			{
				min = t;
				ii = i;
				jj = j;
			}
		}
	res[jj].set[ii] = 1;
	return min;
}
