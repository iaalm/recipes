/*
ID: simonin1
LANG: C++
TASK:inflate
*/

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct task
{
	int point,time;
};

int main()
{
	int time,n,i,j;
	ifstream in("inflate.in");
	ofstream out("inflate.out");
	in >> time >> n;
	vector<task> tk(n);
	int *best = new int[time + 1];
	for(i = 0;i <= time;i++)
	        best[i] = 0;
	for(i = 0;i < n;i++)
		in >> tk[i].point >> tk[i].time;
	for(i = 0;i <= time;i++)
	        for(j = 0;j < n;j++)
	                if(i + tk[j].time <= time && best[tk[j].time + i] < best[i] + tk[j].point)
				best[tk[j].time + i] =  best[i] + tk[j].point;
	for(i = 0,j = 0;i <= time;i++)
	        if(best[i] > j)
	                j = best[i];
	out << j << endl;
	delete best;
}
