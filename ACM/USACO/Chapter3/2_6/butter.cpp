/*
ID: simonin1
LANG: C++
TASK: butter
*/

#include <stdio.h>
#include <string.h>
#include <list>
using namespace std;
struct connect{
	short d,l;
};

unsigned int tab[801][801];

int main(int argc, const char *argv[])
{
	int i,j,k,l;
	int N,n[801],P,C;
	connect ttt;
	list<connect> c[801];
	list<connect>::iterator it1,it2,end;
	FILE* fp = fopen("butter.in","r");
	memset(tab,0x01,801*801*sizeof(unsigned int));
	fscanf(fp,"%d%d%d",&N,&P,&C);
	for(i = 0;i < P;i++)
		tab[i][i] = 0;
	for (i = 0; i < N; i++)
		fscanf(fp,"%d",n+i);
	for (i = 0; i < N; i++)
		n[i]--;
	for (i = 0; i < C; i++) {
		fscanf(fp,"%d%d%d",&j,&k,&l);
		j--;
		k--;
		tab[j][k] = tab[k][j] = l;
	}
	fclose(fp);

	for(i = 0;i < P;i++)
		for(j = 0;j < P;j++)
			for(k = j + 1;k < P;k++)
				if(tab[j][k] > (l = tab[j][i] + tab[i][k]))
					tab[k][j] = tab[j][k] = l;
	
	l = 0x0f000000;
	for(i = 0;i < P;i++){
		k = 0;
		for(j = 0;j < N;j++)
			k += tab[i][n[j]];
		if(k < l)
			l = k;
	}
	fp = fopen("butter.out","w");
	fprintf(fp,"%d\n",l);
	fclose(fp);

	return 0;
}
