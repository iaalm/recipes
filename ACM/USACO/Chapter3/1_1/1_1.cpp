/*
ID: simonin1
LANG: C
TASK:agrinet
*/

#include<stdio.h>
#include<stdlib.h>
#define TRANS(R,L,N) ((R)*(N)+(L))

int Prim(int *table,int num);

int main()
{
	int n,i,j,*table;
	FILE *fp = fopen("agrinet.in","r");
	fscanf(fp,"%d",&n);
	table = (int*) malloc(sizeof(int) * n * n);
	for(i = 0;i < n;i++)
	{
		fgetc(fp);
	        for(j = 0;j < n;j++)
	               fscanf(fp,"%d",table + TRANS(i,j,n));
	}
	fclose(fp);

        fp = fopen("agrinet.out","w");
	fprintf(fp,"%d\n",Prim(table,n));
	fclose(fp);

	free(table);
	return 0;
}

int Prim(int *table,int num)
{
	int i = (num * 8+ sizeof(unsigned int) * 8 - 1) / 8 / sizeof(unsigned int),j,min,index,s,result = 0;
	unsigned int *in = (unsigned int*)malloc(sizeof(unsigned int) * i);
	for(i--;i > 0;i--)
	        in[i] = 0;
	in[0] = 1;
	
	for(s =1;s < num;s++)
	{
		min = 1000000;
		for(i = 0;i < num;i++)
		{
			if((in[i / sizeof(unsigned int)] & (1 << (i % sizeof(unsigned int)))) == 0)
			        continue;
			for(j = 0;j < num;j++)
			{
				if(in[j / sizeof(unsigned int)] & (1 << (j % sizeof(unsigned int))))
				        continue;
				if(table[TRANS(i,j,num)] < min)
				{
					min = table[TRANS(i,j,num)];
					index = j;
				}
			}
		}
		result += min;
		in[index / sizeof(unsigned int)] |= (1 << (index % sizeof(unsigned int)));
	}
	free(in);
	return result;
}
