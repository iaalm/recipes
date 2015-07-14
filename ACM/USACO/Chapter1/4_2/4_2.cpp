/*
ID: simonin1
LANG: C
TASK:clocks
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//#define DEBUG

struct clocks
{
	unsigned short c[9];
};

struct node
{
	struct node *parent;
	unsigned short method;
	struct clocks clock;
	struct node *point;
};

struct clocks add(struct clocks a,const struct clocks b);
unsigned short check(const struct clocks a);
//void printresult(struct node *t,FILE *fp);
void freelist(struct node *head);
unsigned short exist(struct clocks t);

#ifdef DEBUG
void out(struct node *head);
#endif
unsigned short *ex;

int main()
{
	ex = (unsigned short*)malloc(32768);
	const struct clocks table[9]={
	{1,1,0,1,1,0,0,0,0},
	{1,1,1,0,0,0,0,0,0},
	{0,1,1,0,1,1,0,0,0},
	{1,0,0,1,0,0,1,0,0},
	{0,1,0,1,1,1,0,1,0},
	{0,0,1,0,0,1,0,0,1},
	{0,0,0,1,1,0,1,1,0},
	{0,0,0,0,0,0,1,1,1},
	{0,0,0,0,1,1,0,1,1}};
	struct clocks t;
	unsigned short i,finish = 0;
	int deep = 0,j;

	for(j = 0;j < 16384;j++)
		ex[j] ^= ex[j];
		
	struct node *head = (struct node*) malloc(sizeof(struct node)),*p = head,*q,*end = NULL;
	head -> parent = NULL;
	head -> point = NULL;
	head -> method = 8;
	
	FILE *fp = fopen("clocks.in","r");
	for(i = 0;i < 9;i++)
	{
	        fscanf(fp,"%hd",head -> clock.c + i);
	        *(head -> clock.c + i) /= 3;
	        *(head -> clock.c + i) %= 4;
	}
	fclose(fp);

        ex[head -> clock.c[2] + (head -> clock.c[3] << 2) + (head -> clock.c[4] << 4) + (head -> clock.c[5] << 6) + (head -> clock.c[6] << 8) + (head -> clock.c[7] << 10) + (head -> clock.c[8] << 12)] |= (unsigned short)(1 <<(head -> clock.c[0] + (head -> clock.c[1] << 2)));

	do
	{
		p = head;
		while(p != end && !finish)
		{
			for(i = 0;i <= p -> method && !finish;i++)
			{
				t = add(p -> clock,table[i]);
				if(exist(t))
				        continue;
				q = (struct node*) malloc(sizeof(struct node));
				assert(q != NULL);
				q -> parent = p;
				q -> point = head;
				head = q;
				q -> clock = t;
				q -> method = i;

				ex[t.c[2] + (t.c[3] << 2) + (t.c[4] << 4) + (t.c[5] << 6) + (t.c[6] << 8) + (t.c[7] << 10) + (t.c[8] << 12)] |= (1 <<(t.c[0] + (t.c[1] << 2)));
				finish = check(t);
#ifdef DEBUG
out(q);
printf("%X:%hX\n",t.c[2] + (t.c[3] << 2) + (t.c[4] << 4) + (t.c[5] << 6) + (t.c[6] << 8) + (t.c[7] << 10) + (t.c[8] << 12),ex[t.c[2] + (t.c[3] << 2) + (t.c[4] << 4) + (t.c[5] << 6) + (t.c[6] << 8) + (t.c[7] << 10) + (t.c[8] << 12)]);
#endif
			}
			p = p -> point;
		}
#ifdef DEBUG
		printf("deep:%d\n",++deep);
#endif
		end = p;
	}while(!finish);

#ifdef DEBUG
	fclose(fp);
#endif

	fp = fopen("clocks.out","w");
	fprintf(fp,"%hd",head -> method + 1);
	head = head -> parent;
 	while(head -> parent!= NULL)
	{
		
		fprintf(fp," %hd",head -> method + 1);
		head = head -> parent;
	}
	fprintf(fp,"\n");
	fclose(fp);
	freelist(head);
	free(ex);
	return 0;
}

struct clocks add(struct clocks a,const struct clocks b)
{
	int i;
	for(i = 0;i < 9;i++)
	{
		a.c[i] += b.c[i];
		a.c[i] %= 4;
	}
	return a;
}
unsigned short check(const struct clocks a)
{
        int i;
	for(i = 0;i < 9;i++)
	{
		if(a.c[i])
		        return 0;
	}
	return 1;
}
/*void printresult(struct node *head,FILE *fp)
{
 	assert(head != NULL);
	struct node *p,*q,*minindex;
	unsigned short t;
	p = head;
	while(p -> parent != NULL)
	{
		minindex = p;
		q = p;
  		while(q -> parent != NULL)
		{
			q = q -> parent;
			if(q -> method < minindex -> method)
			        minindex = q;
		}
		if(minindex != p)
		{
			t = p -> method;
			p -> method = minindex -> method;
			minindex -> method = t;
			if(p != head)
    			fprintf(fp,"%hd ",p -> method + 1);
		}
		p = p -> parent;
	}
	fprintf(fp,"%hd\n",p -> method + 1);
}*/


void freelist(struct node *head)
{
 struct node *p = head;
	while(p != NULL)
	{
		head = head -> point;
		free(p);
		p = head;
	}
}

unsigned short exist(struct clocks t)
{
	return (ex[t.c[2] + (t.c[3] << 2) + (t.c[4] << 4) + (t.c[5] << 6) + (t.c[6] << 8) + (t.c[7] << 10) + (t.c[8] << 12)] & (1 <<(t.c[0] + (t.c[1] << 2))));
}
#ifdef DEBUG
void out(struct node *head)
{
	FILE *fp = fopen("clocks.dbg","a");
	int i;	
	for(i = 0;i < 9;i++)
			fprintf(fp,"%hd ",head ->clock .c[i]);
		fprintf(fp,":");
	while(head -> parent!= NULL)
	{
		
		fprintf(fp,"%hd ",head -> method + 1);
		head = head -> parent;
	}
	fprintf(fp,"\n");
	fclose(fp);
}
#endif
