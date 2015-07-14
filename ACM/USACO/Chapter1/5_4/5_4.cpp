/*
ID: simonin1
LANG: C
TASK:checker
*/

#include<stdio.h>

unsigned short n,used = 0,board[13];
unsigned int finded = 0;
FILE *fp;

void fill(unsigned short length,unsigned long x,unsigned long y);

int main()
{
	fp = fopen("checker.in","r");
	fscanf(fp,"%hd",&n);
	fclose(fp);
	
	fp = fopen("checker.out","w");
	fill(0,0,0);
	fprintf(fp,"%d\n",finded);
	fclose(fp);
	
	return 0;
}

void fill(unsigned short length,unsigned long x,unsigned long y)
{
	unsigned long k,l;
	unsigned short i,j;
	if(length < n)
	{
		for(i = 0,j = 1;i < n;i++,j <<= 1)
		{
			if(!(used & j))
			{
				used |= j;
				board[length] = i;
							k = 1 << (board[length] + length);
							if(x & k)
							{
								goto end;
							}
							x |= k;

							l = 1 << (board[length] - length + 16);
							if(y & l)
							{
								x &= ~k;
								goto end;
							}
							y |= l;
				
				fill(length + 1,x,y);
				x &= ~k;
				y &= ~l;
			end:
				used &= ~j;
			}
		}
	}
	else
	{
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
