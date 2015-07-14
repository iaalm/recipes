/*
ID: simonin1
LANG: C
TASK: range
*/

#include<stdio.h>

unsigned char tab[250][250];

int main(){
	int n,i,j,k,l;
	char c;
	FILE *fp = fopen("range.in","r");
	fscanf(fp,"%d",&n);
	for(i =0;i < n;i++)
		for(j = 0;j < n;j++){
loop:			c = fgetc(fp);
			switch(c){
				case '1':
					tab[i][j] = 1;break;
				case '0':
					tab[i][j] = 0;break;
				default:
					goto loop;
			}
		}
	fclose(fp);
	fp = fopen("range.out","w");
	k = 1;
	while(1){
		l = 0;
		for(i = 0;i < n - k;i++)
			for(j = 0;j < n - k;j++)
				if(tab[i][j] == k
				&& tab[i][j+1] == k
				&& tab[i+1][j] == k
				&& tab[i+1][j+1] == k){
					tab[i][j] = k + 1;
					l++;
				}
		if(!l)
			break;
		fprintf(fp,"%d %d\n",++k,l);
	}
	fclose(fp);

	return 0;
}
