#include<iostream>
#define abs(X) ((X)>=0?(X):-(X))
using namespace std;

int main()
{
	const int setx[4] = { 1,-1, 0, 0},
	      	  sety[4] = { 0, 0, 1,-1};
	int pla[25][25][25][25],now = 0,i,j,x,y,n,max = 0,ttt;
	short re[390625][4];
	char map[25][27];
	cin >> n;
	for(i = 0;i < 25;i++)
		for(j = 0;j < 25;j++)
			for(x = 0;x < 25;x++)
				for(y = 0;y < 25;y++)
					pla[i][j][x][y] = 12345;
	for(i =0;i < n;i++)
		cin >> map[i];
	for(x =0;x < n;x++)
		for(y =0;y < n;y++)
			if(map[x][y] == '*')
					goto a;
a:	for(i = 0;i < 4;i++)
		if(x + setx[i] >= 0 && x + setx[i] < n && y + sety[i] >= 0 && y + sety[i] < n && map[x + setx[i]][y + sety[i]] != '#')
		{
			re[now][0] = x;
			re[now][1] = y;
			re[now][2] = x + setx[i];
			re[now][3] = y + sety[i];
			pla[x][y][x + setx[i]][y + sety[i]] = 0;
			now++;
		}
	for(i = 0;i < now;i++)
	{
		ttt = pla[re[i][0]][re[i][1]][re[i][2]][re[i][3]] + 1;
		for(j = 0;j < 4;j++)
		{
			x = re[i][2] + setx[j];
			y = re[i][3] + sety[j];
			if(x == re[i][0] && y == re[i][1])
				continue;
			if(x >= 0 && x < n && y >= 0 && y < n && map[x][y] != '#')
			{
				if(ttt != 1 && pla[re[i][0]][re[i][1]][x][y] > ttt)
				{
					re[now][0] = re[i][0];
					re[now][1] = re[i][1];
					re[now][2] = x;
					re[now][3] = y;
					pla[re[i][0]][re[i][1]][x][y] = ttt;
					if(max < ttt)
						max = ttt;
					now++;
				}

				if(x + re[i][0] == re[i][2] * 2 && y + re[i][1] == re[i][3] * 2 && 
						pla[re[i][2]][re[i][3]][x][y] > ttt)
				{
						re[now][0] = x - setx[j];
						re[now][1] = y - sety[j];
						re[now][2] = x;
						re[now][3] = y;
						pla[re[i][2]][re[i][3]][x][y] = ttt;
						if(max < ttt)
							max  = ttt;
						now++;
				}
			}
		}
	}
	cout << max << endl;
	return 0;
}
