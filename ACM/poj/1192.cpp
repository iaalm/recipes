#include<iostream>
#define abs(X) (X>=0?X:-(X))
//#include<fstream>
using namespace std;

struct point
{
	int x,y,q,dir[4],max[4];
} *pp;

int W(int from,int d)
{
	if(pp[from].dir[d] == -1)
		return 0;
	if(pp[from].max[d] != -1)
		return pp[from].max[d];
	int i,t,sum = pp[pp[from].dir[d]].q;
	for(i = 0;i < 4;i++)
		if(d + i != 3 && (t = W(pp[from].dir[d],i)) > 0)
			sum += t;
	if(sum < 0)
		sum = 0;
	pp[from].max[d] = sum;
	return sum;
}

int main()
{
	int n,i,j,max = 0,t;
	cin >> n;
	pp = new point[n];
	for(i = 0;i < n;i++)
	{
		cin >> pp[i].x >> pp[i].y >> pp[i].q;
		for(j = 0;j < 4;j++)
			pp[i].max[j] = pp[i].dir[j] = -1;
		for(j = 0;j < i;j++)
			if(1 == abs(pp[i].x - pp[j].x) + abs(pp[i].y - pp[j].y))
			{
				if(pp[i].x > pp[j].x)
				{
					pp[i].dir[0] = j;
					pp[j].dir[3] = i;
				}
				if(pp[i].x < pp[j].x)
				{
					pp[i].dir[3] = j;
					pp[j].dir[0] = i;
				}
				if(pp[i].y > pp[j].y)
				{
					pp[i].dir[2] = j;
					pp[j].dir[1] = i;
				}
				if(pp[i].y < pp[j].y)
				{
					pp[i].dir[1] = j;
					pp[j].dir[2] = i;
				}
			}
	}
	for(i = 0;i < n;i++)
	{
		t = pp[i].q;
		for(j = 0;j < 4;j++)
		{
			t += W(i,j);
		}
		if(t > max)
			max = t;
	}
	cout << max << endl;
	delete pp;
	return 0;
}
