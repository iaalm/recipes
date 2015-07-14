/*
ID: simonin1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>



int main()
{
	int n,result = 0,i,j,now;
	char neckless[400],t,neck[800]={0};
	FILE *fp = fopen("beads.in","r");
	fscanf(fp,"%d",&n);
	fscanf(fp,"%s",neckless);
	fclose(fp);
	strcat(neck,neckless);
	strcat(neck,neckless);
	n *= 2;

	for(i = 1;i < n;i++)
	{
		t = neck[i - 1];
		if(t == 'w')
		{
			for(j = i - 2;j >= 0;j--)
				if(neck[j] != 'w')
					t = neck[j];
		}
		for(j = i - 1;j >= 0;j--)
			if(neck[j] != t && neck [j] !='w')
				break;
		now = i - j - 1;

		t = neck[i];
		if(t == 'w')
		{
			for(j = i + 1;j < n;j++)
				if(neck[j] != 'w')
					t = neck[j];
		}
		for(j = i;j < n;j++)
			if(neck[j] != t && neck [j] !='w')
				break;
		now += j - i;
		if(now > result)
			result = now;
	}
	if(result > n / 2)
		result = n / 2;          //avoid a loop

	fp = fopen("beads.out","w");
	fprintf(fp,"%d\n",result);
	fclose(fp);
	return 0;
}