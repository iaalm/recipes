#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define N 25
#define M 250

int main()
{
	int i,j,index,n,m = 250;
	m++;
	int* const sq = (int*) malloc(sizeof(int) * m);
	int* const pos = (int*) malloc(sizeof(int) * m * m);
	for(i = 0;i < m;i++)
		sq[i] = i * i;

	for(i = 0;i < m;i++)
		for(j = 0;j < m;j++)
			pos[i * m + j] = sq[i] + sq[j];
	
	for(i = 0;i < m * m;i++)
	{
		index = i;
		for(j = i + 1;j < m * m;j++)
			if(pos[index] > pos[j])
				index = j;
		if(i != index)
		{
			j = pos[i];
			pos[i] = pos[index];
			pos[index] = j;
		}
	}
	index = -1;
	for(i = 0;i < m;i++)
		for(j = 0;j < m;j++)
		{
			if(index != pos[i * m + j])
			{
				printf("%d\n",pos[i * m + j]);
				index = pos[i * m + j];
			}
		}
	free(pos);
	free(sq);
	return 0;
}
