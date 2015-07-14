#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<vector>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<bitset>
#include<map>
#include<utility>
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

struct node
{
	int length,num;
} pip[4];

int nl,M,ex,ey;
void W(int sx,int sy,int n,int us)
{
	if(n ==	 nl)
		return;
	int i,j;
	const int len = pip[n].length,num = pip[n].num;
	if((sx - ex) % len == 0 && (sy - ey) % len == 0 && (i = (abs(sx-ex) + abs(sy -ey)) / len) <= num && M > i + us)
		M = i + us; 
	if(n == nl - 1)
		return ;
	for(i = n,j = 0;i < nl;i++)
		j += pip[i].length * pip[i].num;
	if(abs(sx-ex) + abs(sy -ey) > j)
		return;
	n++;
	for(i = 0;i <= num && i <= M - us;i++)
		for(j = 0;j <= num - i;j++)
		{
			if(M - us < i + j)
				continue;
			W(sx + i * len,sy + j * len,n,us + i + j);
			W(sx - i * len,sy + j * len,n,us + i + j);
			W(sx - i * len,sy - j * len,n,us + i + j);
			W(sx + i * len,sy - j * len,n,us + i + j);
		}
}

int main()
{
	int sx,sy,i;
	scanf("%d %d %d %d %d",&sx,&sy,&ex,&ey,&nl);
	for(i = 0;i < nl;i++)
		scanf("%d",&pip[i].length);
	for(i = 0;i < nl;i++)
		scanf("%d",&pip[i].num);
	M = 50;
	W(sx,sy,0,0);
	if(M == 50)
		printf("-1\n");
	else
		printf("%d\n",M);
	return 0;
}
