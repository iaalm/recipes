/*
ID: simonin1
LANG: C
TASK: gift1
*/
#include<stdio.h>
#include<string.h>

typedef struct 
{
	char name[15];
	int account;
} people;

int main()
{
	unsigned int np,i,j,nr,n;
	people p[10];
	char giver[15],receiver[15];
	int money;
	FILE *fp = fopen("gift1.in","r");
	fscanf(fp,"%d",&np);
	for(i = 0;i < np;i++)
	{
		fscanf(fp,"%s",p[i].name);
		p[i].account = 0;
	}
	for(n = 0;n < np;n++)
	{
		fscanf(fp,"%s",giver);
		fscanf(fp,"%d %d",&money,&nr);
		if(nr == 0)
		{
			/*do
			{
				if(!strcmp(giver,p[i].name))
				{
					p[i].account += money;
					break;
				}
			}while(1);*/
			continue;
		}
		i = 0;
		do
		{
			if(!strcmp(giver,p[i].name))
			{
				p[i].account -= money;
				p[i].account += money % nr;
				break;
			}
			i++;
		}while(1);
		for(i = 0;i < nr;i++)
		{
			fscanf(fp,"%s",receiver);
			j = 0;
			do
			{
				if(!strcmp(receiver,p[j].name))
				{
					p[j].account += money / nr;
					break;
				}
				j++;
			}while(1);
		}
	}//while(!feof(fp));

	fclose(fp);

	fp = fopen("gift1.out","w");
	for(i = 0;i < np;i++)
		fprintf(fp,"%s %d\n",p[i].name,p[i].account);
	fclose(fp);
	return 0;
}