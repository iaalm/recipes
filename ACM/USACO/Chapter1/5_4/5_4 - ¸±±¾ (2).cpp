/*
ID: simonin1
LANG: C
TASK:checker
*/

#include<stdio.h>

unsigned short n,used = 0,board[13];
unsigned int finded = 0;
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
	unsigned long long p = 0,k;
	unsigned short j = 1,q;
	if(length < n)
	{
		for(i = 0,j = 1;i < n;i++,j = j << 1)
		{
			if(!(used & j))
			{
				used |= j;
				board[length] = i;

				                p = 0;
						for(q = 0;q <= length;q++)
						{
							k = 1 << (board[q] + q);
							if(p & k)
							{
								goto end;
							}
							p |= k;
						}

						p = 0;
						for(q = 0;q <= length;q++)
						{
							k = 1 << (board[q] - q + 32);
							if(p & k)
							{
								goto end;
							}
							p |= k;
						}
				
				fill(length + 1);
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
