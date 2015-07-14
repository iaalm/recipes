/*
ID: simonin1
LANG: C
TASK:checker
*/

#include<stdio.h>

unsigned short n,used = 0,board[13],finded = 0;
FILE *fp;

void fill(unsigned short length);

int main()
{
	fp = fopen("checker.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);
	
	fp = fopen("checker.out","w");
	fill(0);
	fprintf(fp,"%d\n",finded);
	fclose(fp);
	
	return 0;
}

void fill(unsigned short length)
{
	unsigned int i = 0;
	unsigned short j = 1,k;
	if(length < n)
	{
		for(i = 0;i < n;i++)
		{
			if(!(used & j))
			{
				used |= j;
				board[length] = i;
				fill(length + 1);
				used &= ~j;
			}
			j = j << 1;
		}
	}
	else
	{
		for(j = 0;j < n;j++)
		{
			k = 1 << (board[j] + j);
			if(i & k)
			{
				return;
				break;
			}
			i |= k;
		}
		
		i = 0;
		for(j = 0;j < n;j++)
		{
			k = 1 << (board[j] - j + 8);
			if(i & k)
			{
				return;
				break;
			}
			i |= k;
		}
		
		finded++;
		if(finded <= 3)
		{
                        fprintf(fp,"%hd",board[0] + 1);
			for(j = 1;j < n;j++)
				fprintf(fp,"% hd",board[j] + 1);
			fprintf(fp,"\n");
		}
	}
}
