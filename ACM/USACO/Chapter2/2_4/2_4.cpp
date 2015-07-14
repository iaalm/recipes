/*
ID: simonin1
LANG: C
TASK:lamps
*/

#include<stdio.h>
#define N 121

int main()
{
	int n,c,on[N],off[N],result[8][N + 1],i = 0,j;
	FILE *fp = fopen("lamps.in","r");
	fscanf(fp,"%d%d",&n,&c);
	do
	{
		fscanf(fp,"%d",on + i);
		i++;
	}while(on[i - 1] != -1);
	i = 0;
	do
	{
		fscanf(fp,"%d",off + i);
		i++;
	}while(off[i - 1] != -1);
	fclose(fp);

	if(c % 2 == 0)
	{
		for(i = 0;i < 20;i++)
		{
			result[0][0 +6 * i] = 1;
			result[0][1 +6 * i] = 1;
			result[0][2 +6 * i] = 1;
			result[0][3 +6 * i] = 1;
			result[0][4 +6 * i] = 1;
			result[0][5 +6 * i] = 1;

			result[1][0 +6 * i] = 1;
			result[1][1 +6 * i] = 1;
			result[1][2 +6 * i] = 0;
			result[1][3 +6 * i] = 0;
			result[1][4 +6 * i] = 0;
			result[1][5 +6 * i] = 1;

			result[2][0 +6 * i] = 1;
			result[2][1 +6 * i] = 0;
			result[2][2 +6 * i] = 1;
			result[2][3 +6 * i] = 0;
			result[2][4 +6 * i] = 1;
			result[2][5 +6 * i] = 0;

			result[3][0 +6 * i] = 1;
			result[3][1 +6 * i] = 0;
			result[3][2 +6 * i] = 0;
			result[3][3 +6 * i] = 1;
			result[3][4 +6 * i] = 0;
			result[3][5 +6 * i] = 0;

			
			result[4][0 +6 * i] = 0;
			result[4][1 +6 * i] = 1;
			result[4][2 +6 * i] = 1;
			result[4][3 +6 * i] = 0;
			result[4][4 +6 * i] = 1;
			result[4][5 +6 * i] = 1;

			result[5][0 +6 * i] = 0;
			result[5][1 +6 * i] = 1;
			result[5][2 +6 * i] = 0;
			result[5][3 +6 * i] = 1;
			result[5][4 +6 * i] = 0;
			result[5][5 +6 * i] = 1;

			result[6][0 +6 * i] = 0;
			result[6][1 +6 * i] = 0;
			result[6][2 +6 * i] = 1;
			result[6][3 +6 * i] = 1;
			result[6][4 +6 * i] = 1;
			result[6][5 +6 * i] = 0;

			result[7][0 +6 * i] = 0;
			result[7][1 +6 * i] = 0;
			result[7][2 +6 * i] = 0;
			result[7][3 +6 * i] = 0;
			result[7][4 +6 * i] = 0;
			result[7][5 +6 * i] = 0;
		}
		for(i = 0;i < 8;i++)
			result[i][N] = 1;
		if(c < 4)
			result[4][N] = 0;
		if(c == 0)
		        result[1][N] = result[2][N] = result[3][N] = result[4][N] = result[5][N] = result[6][N] = result[7][N] = 0;
	}
	else
	{
		for(i = 0;i < 20;i++)
		{
			result[0][0 +6 * i] = 1;
			result[0][1 +6 * i] = 1;
			result[0][2 +6 * i] = 1;
			result[0][3 +6 * i] = 1;
			result[0][4 +6 * i] = 1;
			result[0][5 +6 * i] = 1;

			result[1][0 +6 * i] = 1;
			result[1][1 +6 * i] = 1;
			result[1][2 +6 * i] = 0;
			result[1][3 +6 * i] = 0;
			result[1][4 +6 * i] = 0;
			result[1][5 +6 * i] = 1;

			result[2][0 +6 * i] = 1;
			result[2][1 +6 * i] = 0;
			result[2][2 +6 * i] = 1;
			result[2][3 +6 * i] = 0;
			result[2][4 +6 * i] = 1;
			result[2][5 +6 * i] = 0;

			result[3][0 +6 * i] = 1;
			result[3][1 +6 * i] = 0;
			result[3][2 +6 * i] = 0;
			result[3][3 +6 * i] = 1;
			result[3][4 +6 * i] = 0;
			result[3][5 +6 * i] = 0;

			
			result[4][0 +6 * i] = 0;
			result[4][1 +6 * i] = 1;
			result[4][2 +6 * i] = 1;
			result[4][3 +6 * i] = 0;
			result[4][4 +6 * i] = 1;
			result[4][5 +6 * i] = 1;

			result[5][0 +6 * i] = 0;
			result[5][1 +6 * i] = 1;
			result[5][2 +6 * i] = 0;
			result[5][3 +6 * i] = 1;
			result[5][4 +6 * i] = 0;
			result[5][5 +6 * i] = 1;

			result[6][0 +6 * i] = 0;
			result[6][1 +6 * i] = 0;
			result[6][2 +6 * i] = 1;
			result[6][3 +6 * i] = 1;
			result[6][4 +6 * i] = 1;
			result[6][5 +6 * i] = 0;

			result[7][0 +6 * i] = 0;
			result[7][1 +6 * i] = 0;
			result[7][2 +6 * i] = 0;
			result[7][3 +6 * i] = 0;
			result[7][4 +6 * i] = 0;
			result[7][5 +6 * i] = 0;
		}
		for(i = 0;i < 8;i++)
			result[i][N] = 1;
		if(c < 3)
		{
			result[0][N] = result[1][N] =result[3][N] =result[6][N] = 0;
		}
	}

	for(i = 0;i < 8;i++)
	{
		j = 0;
		while(on[j] != -1)
		{
			if(result[i][on[j] - 1] != 1)
			{
				result[i][N] = 0;
				break;
			}
			j++;
		}

		j = 0;
		while(off[j] != -1)
		{
			if(result[i][off[j] - 1] != 0)
			{
				result[i][N] = 0;
				break;
			}
			j++;
		}
	}

	j = 0;
	fp = fopen("lamps.out","w");
	for(i = 7;i >= 0;i--)
	{
		if(result[i][N] == 0)
			continue;
		for(j = 0;j < n;j++)
			fprintf(fp,"%d",result[i][j]);
		fprintf(fp,"\n");
	}
	if(j == 0)
		fprintf(fp,"IMPOSSIBLE\n");
	fclose(fp);

	return 0;
}
