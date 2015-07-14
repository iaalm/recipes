/*
ID: simonin1
LANG: C
TASK:ariprog
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

short *pos,n;

short check(int a,int b);

int main()
{
	int result[10000][2],NumResult = 0,sq[300],m,num,i,j;
	FILE *fp = fopen("ariprog.in","r");
	assert(fp != NULL);
	fscanf(fp,"%hd",&n);
	fscanf(fp,"%d",&m);
	fclose(fp);
	n--;
	num = 2 * m * m + 1;
	pos = (short*) malloc(sizeof(short) * num);

	for(i = 0;i < num;i++)
		pos[i] = 0;

	for(i = 0;i <= m;i++)
		sq[i] = i * i;

	for(i = 0;i <= m;i++)
		for(j = 0;j <= m;j++)
			pos[sq[i] + sq[j]] = 1;

	for(i = 1;i <= num / n;i++)
		for(j = 0;j <= num - n * i;j++)
		{
			if(pos[j] && check(j,i))
			{
				result[NumResult][0] = j;
				result[NumResult][1] = i;
				NumResult++;
			}
		}

	fp = fopen("ariprog.out","w");
	if(NumResult)
		for(i = 0;i < NumResult;i++)
			fprintf(fp,"%d %d\n",result[i][0],result[i][1]);
	else
		fprintf(fp,"NONE\n");
	fclose(fp);

	return 0;
}


short check(int a,int b)
{
	char i;
	for(i = 0;i < n;i++)
	{
		a += b;
		if(!pos[a])
			return 0;
	}
		return 1;
}
