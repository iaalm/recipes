#include<iostream>

using namespace std;

int X,Y,step,loop;

struct node
{
	char c;
	int i;
};

node mar[10][10];

void work(int i,int j,int t);

int main()
{
	int i,j,start;
	while(1)
	{
		cin >> X >> Y >> start;
		if(X == 0)
			break;

		for(i = 0;i < X;i++)
			for(j = 0;j < Y;j++)
			{
				cin >> mar[i][j].c;
				mar[i][j].i = -1;
			}
		work(0,start - 1,0);
		if(loop == 0)
			cout << step << " step(s) to exit" << endl;
		else
			cout << step << " step(s) before a loop of " << loop << " step(s)" << endl;
	}
	return 0;
}

void work(int i,int j,int t)
{
	if(mar[i][j].i != -1)
	{
		step = mar[i][j].i;
		loop = t - mar[i][j].i;
		return;
	}
	mar[i][j].i = t;
	if(mar[i][j].c == 'N')
		if(i == 0)
		{
			loop = 0;
			step = t + 1;
			return;
		}
		else
			work(i - 1,j,t + 1);
	if(mar[i][j].c == 'S')
		if(i == X - 1)
		{
			loop = 0;
			step = t + 1;
			return;
		}
		else
			work(i + 1,j,t + 1);
	if(mar[i][j].c == 'W')
		if(j == 0)
		{
			loop = 0;
			step = t + 1;
			return;
		}
		else
			work(i,j - 1,t + 1);
	if(mar[i][j].c == 'E')
		if(j == Y - 1)
		{
			loop = 0;
			step = t + 1;
			return;
		}
		else
			work(i,j + 1,t + 1);
}
