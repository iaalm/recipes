/*
ID: simonin1
LANG: C
TASK:milk3
*/

#include<stdio.h>
#include<assert.h>
#define M 1000

struct st
{
	short a[3];
};

short l[3],re[21],pos[M][2];
int n;

void put(short x,short y,struct st sta);

int main()
{
	int i;
	n = 1;
	for(i = 0;i < 20;i++)
		re[i] = 0;
	FILE *fp = fopen("milk3.in","r");
	fscanf(fp,"%d %d %d",l,l+1,l+2);
	fclose(fp);

	re[l[2]] = 1;

	struct st aa;
	aa.a[0] = aa.a[1] = 0;
	aa.a[2] = l[2];
	pos[0][0] = pos[0][1] = 0;
	pos[0][2] = l[2];

	put(0,1,aa);
	put(1,2,aa);
	put(0,2,aa);
	put(1,0,aa);
	put(2,1,aa);
	put(2,0,aa);

	char space[2] = "\0";
	fp = fopen("milk3.out","w");
	for(i = 0;i <= 20;i++)
		if(re[i])
		{
			fprintf(fp,space);
			fprintf(fp,"%d",i);
			space[0] = ' ';
		}
	fprintf(fp,"\n");
	fclose(fp);
	return 0;
}

void put(short x,short y,struct st sta)
{
	int i;
	if(sta.a[x] == 0)
		return;
	if(l[y] - sta.a[y] < sta.a[x])
	{
		sta.a[x] -= (l[y] - sta.a[y]);
		sta.a[y] = l[y];
	}
	else
	{
		sta.a[y] += sta.a[x];
		sta.a[x] = 0;
	}
	for(i = 0;i < n;i++)
	{
		if(pos[i][0] == sta.a[0] && pos[i][1] == sta.a[1])
			return;
	}

	if(sta.a[0] == 0)
	/*re[sta.a[0]] = re[sta.a[1]] = */re[sta.a[2]] = 1;

	pos[n][0] = sta.a[0];
	pos[n][1] = sta.a[1];
	n++;
	assert(n < M);

	put(0,1,sta);
	put(1,2,sta);
	put(0,2,sta);
	put(1,0,sta);
	put(2,1,sta);
	put(2,0,sta);
}
