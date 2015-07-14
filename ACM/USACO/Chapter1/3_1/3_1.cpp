/*
ID: simonin1
LANG: C
TASK:milk
*/

#include<stdio.h>
#include<assert.h>

int main()
{
	int milk,num,i,j,index,farmer[5000][2];
	FILE *fp = fopen("milk.in","r");
	fscanf(fp,"%d %d",&milk,&num);
	for(i = 0;i < num;i++)
	{
		fscanf(fp,"%d %d",&farmer[i][0],&farmer[i][1]);
	}
	fclose(fp);
	
	//sort
	for(i = 0;i < num;i++)
	{
		index = i;
		for(j = i + 1;j < num;j++)
		{
			if(farmer[index][0] > farmer[j][0])
				index = j;
		}
		if(i != index)
		{
			j = farmer[i][0];
			farmer[i][0] = farmer[index][0];
			farmer[index][0] = j;
			j = farmer[i][1];
			farmer[i][1] = farmer[index][1];
			farmer[index][1] = j;
		}
	}
	
	j = 0;
	for(i = 0;milk != 0;i++)
	{
		if(milk < farmer[i][1])
		{
			j += milk * farmer[i][0];
			break;
		}
		else
		{
			milk -= farmer[i][1];
			j += farmer[i][1] * farmer[i][0];
		}
		assert(milk >= 0);
	}
	fp = fopen("milk.out","w");
	fprintf(fp,"%d\n",j);
	fclose(fp);
	return 0;
}


