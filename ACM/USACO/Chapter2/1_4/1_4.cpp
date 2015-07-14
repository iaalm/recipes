/*
ID: simonin1
LANG: C
TASK:holstein
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct nod
{
	struct nod* pre;
	int method;
	int *now;
	struct nod* next;
};

void out(FILE *fp,struct nod *p,int num);

int main()
{
	int m,n,*need,*support,i,j,unfinish = 1;
	FILE *fp = fopen("holstein.in","r");
	fscanf(fp,"%d",&n);
	need = (int*)malloc(sizeof(int) * n);
	for(i = 0;i < n;i++)
		fscanf(fp,"%d",need + i);
	fscanf(fp,"%d",&m);
	support = (int*)malloc(sizeof(int) * n * m);
	for(i = 0;i < m * n;i++)
		fscanf(fp,"%d",support + i);
	fclose(fp);

	struct nod *head = (struct nod*)malloc(sizeof(struct nod)),*p,*q,*r;
	head -> pre = NULL;
	head -> now = (int*)malloc(sizeof(int) * n);
	head -> method = 0;
	head -> next = NULL;
	for(i = 0;i < n;i++)
		head -> now[i] = 0;
	q = head;
	p = head;
		do
		{
			for(i = q -> method;i < m && unfinish;i++)
			{
				r = (struct nod*) malloc(sizeof(struct nod));
				r -> pre = q;
				r -> method = i + 1;
				r -> next = NULL;
				p -> next = r;
				unfinish = 0;
				r -> now = (int*)malloc(sizeof(int) * n);
				p = r;
				for(j = 0;j < n;j++)
				{
					r -> now[j] = q -> now[j] + support[i * n + j];
					if(r -> now[j] < need[j])
						unfinish = 1;
				}
			}
			q = q -> next;
		}while(unfinish);

	fp = fopen("holstein.out","w");
	out(fp,r,0);
	fprintf(fp,"\n");
	fclose(fp);
	
	do
	{
		p = head;
		head = head -> next;;
		free(p -> now);
		free(p);
	}while(head != NULL);

	return 0;
}

void out(FILE *fp,struct nod *p,int num)
{
	if(p -> pre == NULL)
		fprintf(fp,"%d",num);
	else
	{
		out(fp,p -> pre,num + 1);
		fprintf(fp," %d",p -> method);
	}
}
