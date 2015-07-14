#include<stdio.h>
#include<string.h>

char str[6][15] = {"FILL(1)","FILL(2)","DROP(1)","DROP(2)","POUR(1,2)","POUR(2,1)"};

void pr(short i,short n,short tab[][4])
{
	if(i == 0)
		printf("%hd\n",n);
	else
	{
		pr(tab[i][2],n+1,tab);
		puts(str[tab[i][3]]);
	}
}

int main()
{
	short map[110][110],tab[11000][4],now,i,j,a,b,c,p,q,me[6][2];
	memset(map,0,sizeof(map));
	scanf("%hd %hd %hd",&a,&b,&c);
	now = 1;
	tab[0][0] = tab[0][1] = 0;
	for(i = 0;i < now;i++)
	{
		p = tab[i][0];
		q = tab[i][1];
		me[0][0] = a;
		me[0][1] = q;
		me[1][0] = p;
		me[1][1] = b;
		me[2][0] = 0;
		me[2][1] = q;
		me[3][0] = p;
		me[3][1] = 0;
		if(p <= b - q)
		{
			me[4][0] = 0;
			me[4][1] = p + q;
		}
		else
		{
			me[4][0] = p + q - b;
			me[4][1] = b;
		}
		if(q <= a - p)
		{
			me[5][0] = p + q;
			me[5][1] = 0;
		}
		else
		{
			me[5][0] = a;
			me[5][1] = p + q - a;
		}
		for(j = 0;j < 6;j++)
			if(!map[me[j][0]][me[j][1]])
			{
				map[me[j][0]][me[j][1]] = 1;
				tab[now][0] = me[j][0];
				tab[now][1] = me[j][1];
				tab[now][2] = i;
				tab[now][3] = j;
				now++;
				if(me[j][0] == c || me[j][1] == c)
				{
					i = now - 1;
					goto end;
				}
			}
	}
end:	if(now == i)
		puts("impossible");
	else
		pr(i,0,tab);
	return 0;
}
