/*
ID: simonin1
LANG: C
TASK:concom
*/

#include<stdio.h>

short ctrl[100][100] = {0},have[100][100] ={0};

int main()
{
	int i,j = 0,n,a,b,c;
	FILE *fp = fopen("concom.in","r");
	fscanf(fp,"%d",&n);
	for(i = 0;i < n;i++)
	{
		fscanf(fp,"%d %d %d",&a,&b,&c);
		if(a > j)
		        j = a;
		if(b > j)
		        j = b;
		a--;
		b--;
		have[a][b] = c;
		if(c > 50)
		        ctrl[a][b] = 1;
	}
	fclose(fp);
	
	n = j;
	  //a -> b -> c
	for(a = 0;a < n;a++)
	{
		do
		{
			j = 0;//unfinish?
			for(c = 0;c < n;c++)
			{
				if(ctrl[a][c])
				        continue;
				i = 0;                  //totally have
				for(b = 0;b < n;b++)
				{
					if(ctrl[a][b] || a == b)
					i += have[b][c];
				}
				if(i > 50)
				{
					j = 1;
					ctrl[a][c] = 1;
				}
			}
				
		}
		while(j);
	}

	fp = fopen("concom.out","w");
	for(a = 0;a < 100;a++)
	        for(b = 0;b < 100;b++)
	                if(a != b && ctrl[a][b])
	                        fprintf(fp,"%d %d\n",a + 1,b + 1);
	fclose(fp);
	
	return 0;
}
