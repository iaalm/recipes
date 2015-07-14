/*
ID: simonin1
LANG: C
TASK: stamps
*/

#include<stdio.h>
#include<string.h>

int main()
{
	unsigned short nsmp,max,smp[200],i,j;
	unsigned char tab[2000];
	//memset(tab,0xff,sizeof(tab));
	//memset(tab,0xff,sizeof(unsigned char) * 2000);
	for(i = 0;i < 2000;i++)
		tab[i] = 0xff;
	tab[0] = 0;
	FILE *fp = fopen("stamps.in","r");
	fscanf(fp,"%d%d",&max,&nsmp);
	for(i = 0;i < nsmp;i++)
		fscanf(fp,"%d",smp + i);
	fclose(fp);
	
	for(i = 0;tab[i % 2000] <= max;i++)
	{
		for(j = 0;j < nsmp;j++)
			if(tab[(i + smp[j]) % 2000] > tab[i % 2000])
				tab[(i + smp[j]) % 2000] = tab[i % 2000] + 1;
		tab[i % 2000] = 0xff;
	}

	fp = fopen("stamps.out","w");
	fprintf(fp,"%d\n",--i);
	fclose(fp);
	return 0;
}
