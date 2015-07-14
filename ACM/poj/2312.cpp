#include<iostream>
using namespace std;

struct node 
{
	int x,y,s,b;
};

int main()
{
	const int setx[4] = { 1,-1, 0, 0},
	      	  sety[4] = { 0, 0, 1,-1};
	node r[180001];
	char map[300][300];
	int t,i,j,w,h,S;
	while(1)
	{
		S = -1;
		//memset(map,0,sizeof(map));
		//memset(r,0,sizeof(r));
		cin >> h >> w;
		if(h == 0)
			break;
		for(i = 0;i < h;i++)
			for(j = 0;j < w;j++)
			{
				cin >> map[i][j];
				if(map[i][j] == 'Y')
				{
					r[0].x = i;
					r[0].y = j;
					r[0].s = 0;
					r[0].b = 0;
				}
			}
		t = 1;
		for(i = 0;S == -1;i++)
		{
			if(i >= t)
				break;
			if(r[i].b)
			{
				r[t].x = r[i].x;
				r[t].y = r[i].y;
				r[t].s = r[i].s + 1;
				r[t].b = 0;
				t++;
				continue;
			}
			for(j = 0;j < 4;j++)
			{
				r[t].x = r[i].x + setx[j];
				r[t].y = r[i].y + sety[j];
				r[t].s = r[i].s + 1;
				if(r[t].x >= 0 && r[t].x < h && r[t].y >= 0 && r[t].y < w)
				{
					if(map[r[t].x][r[t].y] == 'T')
					{
						S = r[t].s;
						break;
					}
					if(map[r[t].x][r[t].y] == 'E')
					{
						r[t].b = 0;
						map[r[t].x][r[t].y] = 'S';
						t++;
					}
					else if(map[r[t].x][r[t].y] == 'B')
					{
						r[t].b = 1;
						map[r[t].x][r[t].y] = 'S';
						t++;
					}
				}
			}
		}
		cout << S << endl;
	}
	return 0;
}
