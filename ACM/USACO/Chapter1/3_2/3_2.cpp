/*
ID: simonin1
LANG: C
TASK:barn1
*/

#include<stdio.h>
#include<assert.h>

//#define DEBUG
#define M 50
#define N 200

void sort(int* cow,int c);
int main()
{
	int max[M] = {0},i,j,k,n,s,c,begin,t,cha,pre,cow[N];
	FILE *fp;
	fp = fopen("barn1.in","r");
	fscanf(fp,"%d %d %d",&n,&s,&c);
	n--;
	for(k = 0;k < c;k++)
		fscanf(fp,"%d",&cow[k]);
	fclose(fp);
	
	sort(cow,c);
	
	t = cow[c - 1];
	pre = begin = cow[0];
	for(k = 1;k < c;k++)
	{
		cha = cow[k] - pre - 1;
		assert(cha >= 0);
		for(i = 0;i < n;i++)
		{
			if(max[i] < cha)
			{
				for(j = n - 1;j > i;j--)
				{
					max[j] = max[j - 1];
				}
				max[i] = cha;
				break;
			}
		}
		pre = cow[k];
	}
	
#ifdef DEBUG
	for(i = 0;i < n;i++)
	{
		printf("%d ",max[i]);
	}
#endif	
	
	for(i = 0;i < n;i++)
	{
		t -= max[i];
	}
	t -= begin;
	t++;
	
	fp = fopen("barn1.out","w");
	fprintf(fp,"%d\n",t);
	fclose(fp);

#ifdef DEBUG
	getchar();
#endif

	return 0;
}

void sort(int* cow,int c)
{
	int i,j,index;
	for(i = 0;i < c;i++)
	{
		index = i;
		for(j = i + 1;j < c;j++)
		        if(cow[index] > cow[j])
		                index = j;
		if(i != index)
		{
			j = cow[i];
			cow[i] = cow[index];
			cow[index] = j;
		}
	}
}
