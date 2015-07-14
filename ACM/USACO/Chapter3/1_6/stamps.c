/*
ID: simonin1
LANG: C
TASK: stamps
*/

#include<stdio.h>
#include<string.h>

int main()
{
	unsigned long long i;
	unsigned short nsmp,max,smp[200],j;
	unsigned char tab[20000];
	memset(tab,0xff,sizeof(tab));
	tab[0] = 0;
	FILE *fp = fopen("stamps.in","r");
	fscanf(fp,"%hd%hd",&max,&nsmp);
	for(i = 0;i < nsmp;i++)
		fscanf(fp,"%hd",smp + i);
	fclose(fp);
	
	for(i = 0;tab[i % 20000] <= max;i++)
	{
		for(j = 0;j < nsmp;j++)
			if(tab[(i + smp[j]) % 20000] > tab[i % 20000])
				tab[(i + smp[j]) % 20000] = tab[i % 20000] + 1;
		tab[i % 20000] = 0xff;
	}

	fp = fopen("stamps.out","w");
	fprintf(fp,"%d\n",--i);
	fclose(fp);
	return 0;
}
