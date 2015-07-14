#include<stdio.h>
#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<list>
#include<queue>
#define Z(V) cout << #V << ":"<< (V) << endl
using namespace std;
const short setx[4] = { 1,-1, 0, 0},
      	  sety[4] = { 0, 0, 1,-1};
short w,h,Bmap[100][100],Dmap[100][100],Emap[100][100],len,qu[20000][2],tx,ty;
void DFS(short x,short y,short n)
{
	if(n == 0 || Bmap[x][y] < n || (Dmap[x][y] != -1 && Dmap[x][y] <= n))
		return;
	Dmap[x][y] = n++;
	for(short i = 0;i < 4;i++)
		if(x + setx[i] >= 0 && x + setx[i] < w && y + sety[i] >= 0 && y + sety[i] < h && !(Emap[x][y] & (1 << i)))
			DFS(x + setx[i],y + sety[i],n);
}
struct node
{
	short t[4];
};
void Pmap()
{
	int i,j;
	for(i = 0;i < w;i++)
		printf("--");
	putchar(10);
	for(i = h - 1;i >= 0;i--)
	{
		putchar('|');;
		for(j = 0;j < w - 1;j++)
		{
			putchar(' ');
			if(Emap[j][i] & 1)
				putchar('|');
			else
				putchar(' ');
		}
		putchar('|');
		putchar(10);
		if(i == 0)
			break;
		putchar('|');
		for(j = 0;j < w - 1;j++)
		{
			if(Emap[j][i] & 8)
				putchar('-');
			else
				putchar(' ');
			putchar('-');
		}
		putchar(10);
	}
	for(i = 0;i < w;i++)
		printf("--");
	putchar(10);
}
int main()
{
	short T,i,j,now,k,x,y;
	node t;
	bool correct;
	list<node> in;
	list<node>::iterator it,en;
	string str;
	scanf("%hd",&T);
	while(T--)
	{
		correct = true;
		in.clear();
		memset(Bmap,0xff,sizeof(Bmap));
		clr(Dmap);
		clr(Emap);
		scanf("%hd %hd",&w,&h);
		cin >> str;
		len = str.length();
		tx = 0;
		ty = 0;
		for(i = 0;i < len;i++)
			switch(str[i])
			{
				case 'U':ty++;break;
				case 'D':ty--;break;
				case 'L':tx--;break;
				case 'R':tx++;break;
			}
		scanf("%hd",&i);
		while(i--)
		{
			scanf("%hd %hd %hd %hd)",t.t,t.t+1,t.t+2,t.t+3);
			in.insert(in.begin(),t);
			if(t.t[0] == t.t[2])
			{
				if(t.t[1] < t.t[3])
				{
					Emap[t.t[0]][t.t[1]] |= (1 << 2);
					Emap[t.t[2]][t.t[3]] |= (1 << 3);
				}
				else
				{
					Emap[t.t[0]][t.t[1]] |= (1 << 3);
					Emap[t.t[2]][t.t[3]] |= (1 << 2);
				}
			}
			else
			{
				if(t.t[0] < t.t[2])
				{
					Emap[t.t[0]][t.t[1]] |= (1 << 0);
					Emap[t.t[2]][t.t[3]] |= (1 << 1);
				}
				else
				{
					Emap[t.t[0]][t.t[1]] |= (1 << 1);
					Emap[t.t[2]][t.t[3]] |= (1 << 0);
				}
			}
		}
		now = 1;
		qu[0][0] = qu[0][1] = 0;
		Dmap[0][0] = 1;
		Bmap[0][0] = 0;
		for(i = 0;i != now;i++)
		{
			k = Bmap[qu[i][0]][qu[i][1]] + 1;
			for(j = 0;j < 4;j++)
			{
				x = qu[i][0] + setx[j];
				y = qu[i][1] + sety[j];
				if(x < 0 || x >= w || y < 0 || y >= h || (Emap[qu[i][0]][qu[i][1]] & (1 << j)))
					continue;
				if(Bmap[x][y] == -1)
				{
					Bmap[x][y] = k;
					Dmap[x][y] = Dmap[qu[i][0]][qu[i][1]];
					qu[now][0] = x;
					qu[now][1] = y;
					now++;
				}
				else if(Bmap[x][y] == k && Dmap[x][y] != 2)
				{
					Dmap[x][y] = 2;
					qu[now][0] = x;
					qu[now][1] = y;
					now++;
				}
			}
		}
		if(Bmap[tx][ty] != len || Dmap[tx][ty] == 2)
		{
			correct = false;
			goto end;
		}
		for(it = in.begin(),en = in.end();it != en;it++)
		{
			memset(Dmap,0xff,sizeof(Dmap));
			DFS(it->t[0],it->t[1],Bmap[it->t[2]][it->t[3]] + 1);
			DFS(it->t[2],it->t[3],Bmap[it->t[0]][it->t[1]] + 1);
			if(Dmap[tx][ty] > len || Dmap[tx][ty] == -1)
			{
				correct = false;
				goto end;
			}
		}
end:		if(correct)
			printf("CORRECT\n");
		else
			printf("INCORRECT\n");
		//Pmap();
	}
	return 0;
}

