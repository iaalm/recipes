/*
ID: simonin1
LANG: C
TASK:numtri
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int num,max;
} nod;

int conv(int col,int row);

int main()
{
	int n,i,j,maxnum;
	FILE *fp = fopen("numtri.in","r");
	fscanf(fp,"%d",&n);
	nod* const arr = (nod*)malloc(sizeof(nod) * n * (n + 1) / 2);
	for(i = 0;i < n;i++)
	        for(j = 0;j <= i;j++)
			fscanf(fp,"%d",&arr[conv(i,j)].num);
	fclose(fp);
	
	arr[0].max = arr[0].num;
	
	for(i = 1;i < n;i++)
	{
		arr[conv(i,0)].max = arr[conv(i,0)].num + arr[conv(i - 1,0)].max;
	        for(j = 1;j < i;j++)
	        {
			if(arr[conv(i - 1,j)].max > arr[conv(i - 1,j - 1)].max)
			        arr[conv(i,j)].max = arr[conv(i,j)].num + arr[conv(i - 1,j)].max;
   			else
   			        arr[conv(i,j)].max = arr[conv(i,j)].num + arr[conv(i - 1,j - 1)].max;
		}
		arr[conv(i,i)].max = arr[conv(i,i)].num + arr[conv(i - 1,i - 1)].max;
	}
	
	i = n - 1;
	maxnum = 0;
	for(j = 0;j < n;j++)
	{
		if(maxnum < arr[conv(i,j)].max)
		        maxnum = arr[conv(i,j)].max;
	}
	
	fp = fopen("numtri.out","w");
	fprintf(fp,"%d\n",maxnum);
	fclose(fp);
	
	return 0;
}

int conv(int col,int row)
{
	return col * (col + 1) / 2 + row;
}
