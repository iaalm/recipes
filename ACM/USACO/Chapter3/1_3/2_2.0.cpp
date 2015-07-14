/*
ID: simonin1
LANG: C++
TASK:humble
*/

#include<fstream>
#include<bitset>

#define MAX 1000000

using namespace std;

int next(bitset<MAX>& t)
{
	static int now = 0;
	do
	{
		now++;
	}while(t.test(now) != 1);
	return now;
}

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	int gk,gn,i,j,now;
	in >> gk >> gn;
	int *gp = new int[gk];
	for(i = 0;i < gk;i++)
	        in >> gp[i];
	bitset<MAX> a(0);
	a.reset();
	a.set(1);
	for(i = 0;i < gn;i++)
	{
		now = next(a);
		for(j = 0;j < gk;j++)
		        a.set(now * gp[j]);
	}
	out << next(a) << endl;
	delete gp;
	return 0;
}
