/*
ID: simonin1
LANG: C++
TASK:humble
*/

#include<fstream>

using namespace std;

int gk,gn,*gp,*gi;
unsigned int *res,*resi;
unsigned int getNext(int n);

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	int i;
	in >> gk >> gn;
	gp = new int[gk];
	gi = new int[gk];
	for(i = 0;i < gk;i++)
	{
	        in >> gp[i];
		gi[i] = 0;
	}
	res = new unsigned int[gn];
	resi = new unsigned int[gn + 1]; 
	res[0] = 1;
	resi[0] = 0;
	for(i = 1;i < gn;i++)
		res[i] = getNext(i);
	
	out << getNext(gn) << endl;
	return 0;
}

unsigned int getNext(int n)
{
	unsigned int min = 0 - 1,t,i,ii;
	for(i = 0;i < gk;i++)
	{
		for(t = gi[i];t < n;t++)
			if(resi[t] <= i)
			{
				gi[i] = t;
				break;
			}
		t = res[gi[i]] * gp[i];
		if(t < min)
		{
			min = t;
			ii = i;
		}
	}
	resi[n] = ii;
	gi[ii]++;
	return min;
}
