#include<stdio.h>
#include<string.h>

struct node
{
	short x,y,n;
	char tab[20][20];
} qu[1 << 19];

int main()
{
	const short 	setx[4] = {-1, 0, 0, 1},
	      		sety[4] = { 0,-1, 1, 0};
	int w,h,now,i,j,x,y;
	while(1)
	{
		scanf("%d %d",&w,&h);
		if(w == 0)
			return 0;
		for(i = 0;i < h;i++)
			for(j = 0;j < w;j++)
			{
				scanf("%d",&x);
				if(x == 2)
				{
					qu[0].x = i;
					qu[0].y = j;
					x = 0;
				}
				qu[0].tab[i][j] = x;
			}
		qu[0].n = 0;
		for(i = 0,now = 1;i < now && qu[i].n < 10;i++)
			for(j = 0;j < 4;j++)
			{
				x = qu[i].x + setx[j];
				y = qu[i].y + sety[j];
				if(x == -1 || x == h || y == -1 || y == w || qu[i].tab[x][y] == 1)
					continue;
				if(qu[i].tab[x][y] == 3)
					goto end;
				for(x += setx[j],y += sety[j];x >= 0 && x < h && y >= 0 && y < w;x += setx[j],y += sety[j])
				{
					if(qu[i].tab[x][y] == 3)
						goto end;
					if(qu[i].tab[x][y] == 1)
					{
						memcpy(qu[now].tab,qu[i].tab,800);
						qu[now].tab[x][y] = 0;
						qu[now].n = qu[i].n + 1;
						qu[now].x = x - setx[j];
						qu[now].y = y - sety[j];
						now++;
						break;
					}

					
				}
			}
end:		if(i == now || qu[i].n == 10)
			printf("-1\n");
		else
			printf("%d\n",qu[i].n + 1);
	}
}
