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
	int n,result = 0,i,before = 0,now = 0;
	char neck[400],t = 'q';
	FILE *fp = fopen("beads.in","r");
	fscanf(fp,"%d",&n);
	fscanf(fp,"%s",neck);
	fclose(fp);
	
	for(i = 0;i < n;i++)
	{
		if(neck[i] != t && neck[i] !='w')
		{
			t = neck[i];
			if(before + now > result)
				result = before + now;
			before = now;
			now = 0;
		}
		else
			now ++;

	}

	for(i = 0;i < n;i++)
	{
		if(neck[i] != t && neck[i] !='w')
		{
			t = neck[i];
			if(before + now > result)
				result = before + now;
			before = now;
			now = 0;
		}
		else
			now ++;

	}
	if(before + now > result)
		result = before + now;
	if(result > n)
		result = n;

	fp = fopen("beads.out","w");
	fprintf(fp,"%d\n",result);
	fclose(fp);
	return 0;
}