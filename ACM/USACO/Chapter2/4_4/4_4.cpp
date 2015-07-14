/*
ID: simonin1
LANG: C
TASK:comehome
*/

#include<stdio.h>
#define MAX_P 52
#define MAX_S 25
#define MAX_INT 1073741823
#define tran(X) ((X) > 'Z'?(X) - 'a' + 26:(X) - 'A')

int shortest[MAX_P];
char mark[MAX_P];
int table[MAX_P][MAX_P];

void work(int point);

int main()
{
	int i,j;
	char k,l;
	FILE *fp = fopen("comehome.in","r");
	fscanf(fp,"%d",&i);
	while(i != 0)
	{
		fscanf(fp,"%c",&k);   //\n
		fscanf(fp,"%c %c %d",&k,&l,&j);
		if(table[tran(k)][tran(l)] > j || table[tran(k)][tran(l)] == 0)
			table[tran(k)][tran(l)] = table[tran(l)][tran(k)] = j;
		i--;
	}
	fclose(fp);
	for(i = 0;i < MAX_S;i++)
	        mark[i] = 'A' + i;
	for(i = MAX_S;i < MAX_P;i++)
	        shortest[i] = MAX_INT;

	for(i = 0;i < MAX_P;i++)
		work(i);
		
        fp = fopen("comehome.out","w");
        fprintf(fp,"%c %d\n",mark[MAX_S],shortest[MAX_S]);
        fclose(fp);
        
        return 0;
}

void work(int point)
{
	int i;
	for(i = MAX_S;i < MAX_P;i++)
		if(table[point][i] != 0 && shortest[point] + table[point][i] < shortest[i])
		{
			shortest[i] = shortest[point] + table[point][i];
			mark[i] = mark[point];
			work(i);
		}
}
