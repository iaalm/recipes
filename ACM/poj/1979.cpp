#include<stdio.h>

char map[20][21];
int W,H;

int DFS(int x,int y)
{
	if(x < 0 || x >= H || y < 0 || y >= W || map[x][y] == '#')
		return 0;
	map[x][y] = '#';
	return 1 + DFS(x - 1,y) + DFS(x + 1,y) + DFS(x,y - 1) + DFS(x,y + 1);
}

int main()
{
	int i,j,x,y;
	while(1)
	{
		scanf("%d %d",&W,&H);
		if(W == 0)
			return 0;
		gets(map[0]);
		for(i = 0;i < H;i++)
		{
			gets(map[i]);
			for(j = 0;j < W;j++)
				if(map[i][j] == '@')
				{
					x = i;
					y = j;
				}
		}
		printf("%d\n",DFS(x,y));
	}
}
