#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
using namespace std;
struct node
{
	int x,y,s;
};

int main()
{
	const int setx[8] = { 2, 2, 1, 1,-2,-2,-1,-1},
	      	  sety[8] = { 1,-1, 2,-2, 1,-1, 2,-2};
	int map[9][9],x,y,t,res,i,j;
	node rec[83];
	char sa[3],sb[3];
	while(scanf("%s %s",sa,sb) != -1)
	{
		memset(map,0, sizeof(map));
		res = -1;
		rec[0].x = sa[0] - 'a';
		rec[0].y = sa[1] - '1';
		rec[0].s = 0;
		x = sb[0] - 'a';
		y = sb[1] - '1';
		t = 1;
		for(i = 0;res == -1;i++)
		{
			if(rec[i].x == x && rec[i].y == y)
			{
				res = rec[i].s;
				break;
			}
			for(j = 0;j < 8;j++)
			{
				rec[t].x = rec[i].x + setx[j];
				rec[t].y = rec[i].y + sety[j];
				rec[t].s = rec[i].s + 1;
				if(rec[t].x >= 0 && rec[t].y >= 0 && rec[t].x < 8 && rec[t].y < 8 && map[rec[t].x][rec[t].y] == 0)
				{
					map[rec[t].x][rec[t].y] = 1;
					t++;
				}
			}
		}
		printf("To get from %s to %s takes %d knight moves.\n",sa,sb,res);
	}
	return 01;
}
