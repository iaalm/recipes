/*
ID: simonin1
LANG: C
TASK:frac1
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct nod
{
	int fz,fm;
	struct nod *p;
}num;

int good(int i,int j);
int biger(num a,num b);

int main()
{
	int n,fm,fz;
	num *head = NULL,*p,*q,*index;
	FILE *fp = fopen("frac1.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);

	for(fm = 2;fm <= n;fm++)
		for(fz = 1;fz < fm;fz++)
			if(good(fz,fm))
			{
				p = (num*) malloc(sizeof(num));
				p -> p = head;
				head = p;
				p -> fz = fz;
				p -> fm = fm;
			}
	p = (num*)malloc(sizeof(num));
	p -> fz = 0;
	p -> fm = 1;
	p -> p = head;
	head = p;	

	p = head;
	while(p -> p != NULL)
	{
		index = p;
		q = p;
		while(q -> p != NULL)
		{
			if(biger(*(index -> p),*(q -> p)))
				index = q;
			q = q -> p;
		}
		if(p != index)
		{
			q = p -> p;
			p -> p = index -> p;
			index -> p = q;

			q = p -> p -> p;
			p -> p -> p = index -> p -> p;
			index -> p -> p = q;
		}
		p = p -> p;
		
	}
	fp = fopen("frac1.out","w");
	do
	{
		p = head;
		fprintf(fp,"%d/%d\n",head -> fz,head -> fm);
		head = head -> p;
		free(p);
	}while(head != NULL);
	fprintf(fp,"1/1\n");
	fclose(fp);

	return 0;
}

int good(int i,int j)
{
	int k;
	for(k = 2;k <= i;k++)
		if(!(i % k || j % k))
			return 0;
	return 1;
}
int biger(num a,num b)
{
	return ((a.fz * b.fm) > (a.fm * b.fz));
}
