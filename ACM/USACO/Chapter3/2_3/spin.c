/*
ID: simonin1
LANG: C
TASK: spin
*/

#include<stdio.h>
#include<string.h>

int main(){
	int space[5][5][2],speed[5],count[5],i,j,k,l,end;
	char ang[360];
	FILE *fp = fopen("spin.in","r");
	for(i = 0;i < 5;i++)
	{
		fscanf(fp,"%d %d",speed + i, count + i);
		for(j = 0;j < count[i];j++)
			fscanf(fp,"%d %d",&space[i][j][0], &space[i][j][1]);
	}
	fclose(fp);

	fp = fopen("spin.out","w");
	for(i = 0;i < 360;i++){
		bzero(ang,360);
		for(j = 0;j < 5;j++){
			for(k = 0;k < count[j];k++){
				end = space[j][k][0] + space[j][k][1] + speed[j] * i;
				for(l = space[j][k][0] + speed[j] * i;l <= end;l++)
					ang[l % 360]++;
			}
		}
		for(j = 0;j < 360;j++)
			if(ang[j] == 5){
				fprintf(fp,"%d\n",i);
				fclose(fp);
				return 0;
			}
	}
	fprintf(fp,"none\n");
	fclose(fp);
	return 0;
}
