/*
ID: simonin1
LANG: C
TASK:nocows
*/

#include<stdio.h>
#include<assert.h>

int wtable[101][201];
int ntable[101][201];

int work(int level,int nod);
int nomore(int level,int nod);
int pow2(int n);

int main()
{
	int n,k,i,j,max;
	FILE *fp = fopen("nocows.in","r");
	fscanf(fp,"%d %d",&n,&k);
	fclose(fp);

	for(i = 0;i < 201;i++)
		wtable[0][i] = ntable[0][i] = 0;
	for(i = 1;i <= k;i++)
	{
		if(i < 9)
			max = pow2(i);
		else
			max= 300;
		for(j = 1;j < 2 * i;j++)
			wtable[i][j] = 0;
		for(j = 2 * i;j < max && j <= n;j++)
			wtable[i][j] = -1;
		for(j = max;j <= n;j++)
			wtable[i][j] = 0;
		for(j = 1;j < n && j < max;j++)
			ntable[i][j] = -1;
		for(j = max;j < n;j++)
			ntable[i][j] = 0;
		if(max <= n)
			wtable[i][max - 1] = ntable[i][max - 1] = ntable[i][1] = 1;
		if(2 * i - 1 <= n)
			wtable[i][2 * i - 1] = pow2(i - 2);
	}

	wtable[1][1] = ntable[1][1] = 1;

	fp = fopen("nocows.out","w");
	fprintf(fp,"%d\n",(work(k,n) % 9901));
	fclose(fp);

	for(i = 0;i < 201;i++)
		printf("%8d",i);
	printf("\n");
	for(i = 1;i < 101;i++)
	{
		printf("%7d:",i);
		for(j = 1;j < 201;j++)
			printf("%8d",wtable[i][j]);
		printf("\n");
	}
	
	printf("\n");

	for(i = 0;i < 201;i++)
		printf("%8d",i);
	printf("\n");
	for(i = 1;i < 101;i++)
	{
		printf("%7d:",i);
		for(j = 1;j < 201;j++)
			printf("%8d",ntable[i][j]);
		printf("\n");
	}
	return 0;
}

int work(int level,int nod)             //未对偶数剪枝
{
	int i = wtable[level][nod],j,k,result = 0;
	if(i != -1)
		return i;
	for(i = 1;i < nod - 1;i++)
	{
			result += ((work(level - 1,i) * nomore(level - 2,nod - i - 1)) % 9901 + (work(level - 1,nod - i - 1) * nomore(level - 2,i)) % 9901 + (work(level - 1,i) * work(level - 1, nod - i - 1)) % 9901);  
	}
	assert(result >= 0);
	result = result % 9901;
	wtable[level][nod] = result;
	return result;

}
int nomore(int level,int nod)
{
	if(level == 0 || nod <= 0)
		return 0;
	int result = ntable[level][nod];
	if(result != -1)
		return result;
	result = ((work(level,nod) + nomore(level - 1,nod)) % 9901);
	ntable[level][nod] = result;
	return result;
}
int pow2(int n)
{
	int i,result = 1;
	for(i = 0;i < n;i++)
	{
		result *= 2;
		result %= 9901;
	}
	return result;
}
