#include<iostream>
using namespace std;

struct point
{
	int num,step,bin,fx,fy;
};

struct node
{
	int x,y,num,step,fx,fy,bin;
};
const int setx[4] = { 1,-1, 0, 0},
      	  sety[4] = { 0, 0, 1,-1};
int main()
{
	point map[210][210];
	node record[41000];
	int i,j,N,precord = 0,x,y,z;
	cin >> N;
	if(N == 1)
	{
		cin >> N;
		cout << N << endl;
		return 0;
	}
	for(i = 0;i < N;i++)
		for(j = 0;j < N;j++)
		{
			cin >> map[i][j].num;
			map[i][j].bin = 0;
			if(map[i][j].num != 0)
			{
				record[precord].x = i;
				record[precord].y = j;
				record[precord].fx = i;
				record[precord].fy = j;
				map[i][j].fx = i;
				map[i][j].fy = j;
				record[precord].num = map[i][j].num;
				record[precord].step = 0;
				record[precord].bin = 0;
				precord++;
				map[i][j].step = 0;
			}
			else
			{
				map[i][j].step = 41000;
			}
		}
	for(i = 0;i != N * N && precord > i;i++)
	{
		if(map[record[i].x][record[i].y].bin)
			record[i].bin = 1;
		for(j = 0;j <4;j++)
		{
			x = record[i].x + setx[j];
			y = record[i].y + sety[j];
			if(x < 0 || x >= N || y < 0 || y >= N || map[x][y].step < record[i].step + 1)
				continue;
			if(map[x][y].step == record[i].step + 1)
			{
				if(!record[i].bin && record[i].fx == map[x][y].fx && record[i].fy == map[x][y].fy)
					continue;
				map[x][y].bin = 1;
/*				for(z = 0;z < 4;z++)
					if(map[x + setx[z]][y + sety[z]].step == map[x][y].step + 1)
						map[x + setx[z]][y + sety[z]].bin = 1;
*/			}
			else
			{
				record[precord].x = x;
				record[precord].y = y;
				record[precord].fx = record[i].fx;
				record[precord].fy = record[i].fy;
				record[precord].num = record[i].num;
				record[precord].bin = record[i].bin;
				map[x][y].bin = record[i].bin;
				map[x][y].fx = record[i].fx;
				map[x][y].fy = record[i].fy;
				record[precord].step = record[i].step + 1;
				map[x][y].step = record[i].step + 1;
				map[x][y].num = record[i].num;
				precord++;
			}
		}
	}
	for(i = 0;i < N;i++)
		for(j = 0;j < N;j++)
		{
			if(map[i][j].bin == 1)
				cout << 0;
			else
				cout << map[i][j].num;
			if(j == N - 1)
				cout << " " << endl;
			else
				cout << " ";
		}
	return 0;
}
