/*
ID: simonin1
LANG: C
TASK: packrec
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 4

typedef struct List
{
	int x;                  //x <= y;
	int y;
	struct List *point;
} list;

typedef struct
{
	int minx;
	int miny;
	int maxx;
	int maxy;
	int lx;
	int ly;
} block;

int max = 100000;
list *head = NULL;

void work(block *b);
void sort(list* head);
void freelist(list *head);
short check(block *b,int j);

int main()
{
	block b[N];
	list *t;
	int i;
	FILE *fp = fopen("packrec.in","r");
	for(i = 0;i < N;i++)
	{
		fscanf(fp,"%d %d",&b[i].lx,&b[i].ly);
		b[i].minx = b[i].miny = b[i].maxx = b[i].maxy = 0;
	}
	fclose(fp);
	
	for(i = 0;i < N;i++)
	{
		b[i].maxx = b[i].lx;
		b[i].maxy = b[i].ly;
		work(b);
		b[i].maxx = b[i].minx;
		b[i].maxy = b[i].miny;
	}

	sort(head);

	fp = fopen("packrec.out","w");
	fprintf(fp,"%d\n",max);
	t = head;
	do
	{
		fprintf(fp,"%d %d\n",t -> x,t ->y);
		t = t -> point;
	}while(t != NULL);
	fclose(fp);
	freelist(head);
	
	return 0;
}

void sort(list* head)                  //若作为库,需大幅改进
{
	assert(head != NULL);
	list *p,*q,*minindex;
	int t;
	p = head;
	while(p -> point != NULL)
	{
		minindex = p;
		q = p;
  		while(q -> point != NULL)
		{
			q = q -> point;
			if(q -> x < minindex -> x)
			        minindex = q;
		}
		if(minindex != p)
		{
			t = p -> x;
			p -> x = minindex -> x;
			minindex -> x = t;
			t = p -> y;
			p -> y = minindex -> y;
			minindex -> y = t;
		}
		p = p -> point;
	}
	p = head;
	while(p -> point != NULL)
	{
                q = p -> point;
		if(p -> x == q -> x && p -> y == q -> y)
		{
			p -> point = q -> point;
			free(q);
			continue;
		}
                p = q;
	}
}

void freelist(list *head)
{
	list *p = head;
	while(p != NULL)
	{
		head = head -> point;
		free(p);
		p = head;
	}
}

void work(block *b)
{
	short filled = 1,i,j;
	int minx,maxx,miny,maxy,area;
	list *p;
	for(i = 0;i < N;i++)
	{
		if(b[i].minx == b[i].maxx)
		{
			filled = 0;
			for(j = 0;j < N;j++)
			{
                                if(b[j].minx != b[j].maxx)
                                {
     					b[i].minx = b[j].maxx;
					b[i].maxx = b[i].minx + b[i].lx;
					b[i].miny = b[j].miny;
					b[i].maxy = b[i].miny + b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxx = b[j].minx;
					b[i].minx = b[i].maxx - b[i].lx;
    					b[i].miny = b[j].miny;
					b[i].maxy = b[i].miny + b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].minx = b[j].maxx;
					b[i].maxx = b[i].minx + b[i].ly;
					b[i].miny = b[j].miny;
					b[i].maxy = b[i].miny + b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxx = b[j].minx;
					b[i].minx = b[i].maxx - b[i].ly;
    					b[i].miny = b[j].miny;
					b[i].maxy = b[i].miny + b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;
					//
                                        b[i].miny = b[j].maxy;
					b[i].maxy = b[i].miny + b[i].ly;
					b[i].minx = b[j].minx;
					b[i].maxx = b[i].minx + b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxy = b[j].miny;
					b[i].miny = b[i].maxy - b[i].ly;
    					b[i].minx = b[j].minx;
					b[i].maxx = b[i].minx + b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].miny = b[j].maxy;
					b[i].maxy = b[i].miny + b[i].lx;
					b[i].minx = b[j].minx;
					b[i].maxx = b[i].minx + b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxy = b[j].miny;
					b[i].miny = b[i].maxy - b[i].lx;
    					b[i].minx = b[j].minx;
					b[i].maxx = b[i].minx + b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;
					///////////////////////
     					b[i].minx = b[j].maxx;
					b[i].maxx = b[i].minx + b[i].lx;
					b[i].maxy = b[j].maxy;
					b[i].miny = b[i].maxy - b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxx = b[j].minx;
					b[i].minx = b[i].maxx - b[i].lx;
    					b[i].maxy = b[j].maxy;
					b[i].miny = b[i].maxy - b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].minx = b[j].maxx;
					b[i].maxx = b[i].minx + b[i].ly;
					b[i].maxy = b[j].maxy;
					b[i].miny = b[i].maxy - b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxx = b[j].minx;
					b[i].minx = b[i].maxx - b[i].ly;
    					b[i].maxy = b[j].maxy;
					b[i].miny = b[i].maxy - b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;
					//
                                        b[i].miny = b[j].maxy;
					b[i].maxy = b[i].miny + b[i].ly;
					b[i].maxx = b[j].maxx;
					b[i].minx = b[i].maxx - b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxy = b[j].miny;
					b[i].miny = b[i].maxy - b[i].ly;
    					b[i].maxx = b[j].maxx;
					b[i].minx = b[i].maxx - b[i].lx;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].miny = b[j].maxy;
					b[i].maxy = b[i].miny + b[i].lx;
					b[i].maxx = b[j].maxx;
					b[i].minx = b[i].maxx - b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;

					b[i].maxy = b[j].miny;
					b[i].miny = b[i].maxy - b[i].lx;
    					b[i].maxx = b[j].maxx;
					b[i].minx = b[i].maxx - b[i].ly;
					if(check(b,i))
						work(b);
					b[i].maxx = b[i].minx;
				}
			}
		}
	}
	if(filled)
	{/*
for(i = 0;i < N;i++)
printf("%5d %5d %5d %5d\n",b[i].minx,b[i].maxx,b[i].miny,b[i].maxy);
printf("\n");*/
		minx = maxx = miny = maxy = 0;
		for(i = 0;i < N;i++)
		{
			if(b[i].minx < minx)
			        minx = b[i].minx;
			if(b[i].maxx > maxx)
			        maxx = b[i].maxx;
			if(b[i].miny < miny)
			        miny = b[i].miny;
			if(b[i].maxy > maxy)
			        maxy = b[i].maxy;
		}
		area = (maxx - minx) * (maxy - miny);
		if(area < max)
		{
			max = area;
			freelist(head);
			head = (list*)malloc(sizeof(list));
			head -> x = maxx - minx;
			head -> y = maxy - miny;
			head -> point = NULL;
			if(head -> x > head -> y)
			{
				maxx = head -> x;
				head -> x =head -> y;
				head -> y = maxx;
			}
		}
		else if(area == max)
		{
			p = (list*)malloc(sizeof(list));
			p -> point = head;
			head = p;
			head -> x = maxx - minx;
			head -> y = maxy - miny;
			if(head -> x > head -> y)
			{
				maxx = head -> x;
				head -> x =head -> y;
				head -> y = maxx;
			}
		}
	}
}

short check(block *b,int j)
{
	short i;
	for(i = 0;i < N;i++)
	{
		if(i != j && b[i].maxx != b[i].minx)
		{
			if(((b[j].maxx > b[i].minx && b[j].maxx <= b[i].maxx) || (b[j].minx >= b[i].minx && b[j].minx < b[i].maxx)
			||  (b[i].maxx > b[j].minx && b[i].maxx <= b[j].maxx) || (b[i].minx >= b[j].minx && b[i].minx < b[j].maxx))
			&& ((b[j].maxy > b[i].miny && b[j].maxy <= b[i].maxy) || (b[j].miny >= b[i].miny && b[j].miny < b[i].maxy)
			||  (b[i].maxy > b[j].miny && b[i].maxy <= b[j].maxy) || (b[i].miny >= b[j].miny && b[i].miny < b[j].maxy)))
			        return 0;
		}
	}
	return 1;
}
