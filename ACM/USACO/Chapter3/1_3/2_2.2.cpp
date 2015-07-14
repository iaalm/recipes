/*
ID: simonin1
LANG: C++
TASK:humble
*/

#include<fstream>

using namespace std;

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	int gk,gn,i,now = 0,*gp;
	unsigned long long j;
	in >> gk >> gn;
	gp = new int[gk];
	for(i = 0;i < gk;i++)
	        in >> gp[i];
	for(j = 1;now < gn;j++)
		for(i = 0;i < gk;i++)
			if(j % gp[i] == 0)
			{
				now++;
				break;
			}
	out << j << endl;
	delete[] gp;
	return 0;
}
