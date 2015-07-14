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
	short c[9];
};

struct node
{
	struct node *parent;
	short method;
	struct clocks clock;
	struct node *point;
};

struct clocks add(struct clocks a,const struct clocks b);
short check(const struct clocks a);
//void printresult(struct node *t,FILE *fp);
void freelist(struct node *head);
short exist(struct node *head,struct clocks t);

#ifdef DEBUG
void out(struct node *head);
#endif

int main()
{
	const struct clocks table[9]={
	{3,3,0,3,3,0,0,0,0},
	{3,3,3,0,0,0,0,0,0},
	{0,3,3,0,3,3,0,0,0},
	{3,0,0,3,0,0,3,0,0},
	{0,3,0,3,3,3,0,3,0},
	{0,0,3,0,0,3,0,0,3},
	{0,0,0,3,3,0,3,3,0},
	{0,0,0,0,0,0,3,3,3},
	{0,0,0,0,3,3,0,3,3}};
	struct clocks t;
	short i,finish = 0;

	struct node *head = (struct node*) malloc(sizeof(struct node)),*p = head,*q;
	head -> parent = NULL;
	head -> point = NULL;
	head -> method = 9;
	
	FILE *fp = fopen("clocks.in","r");
	for(i = 0;i < 9;i++)
	        fscanf(fp,"%hd",head -> clock.c + i);
	fclose(fp);

	do
	{
		p = head;
		while(p != NULL && !finish)
		{
			for(i = 0;i < p -> method && !finish;i++)
			{
				t = add(p -> clock,table[i]);
				if(exist(head,t))
				        continue;
				q = (struct node*) malloc(sizeof(struct node));
				assert(q != NULL);
				q -> parent = p;
				q -> point = head;
				head = q;
				q -> clock = t;
				q -> method = i;
				finish = check(t);
#ifdef DEBUG
out(q);
#endif
			}
			p = p -> point;
		}
		printf("deep+1");
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
	return 0;
}

struct clocks add(struct clocks a,const struct clocks b)
{
	int i;
	for(i = 0;i < 9;i++)
	{
		a.c[i] += b.c[i];
		a.c[i] %= 12;
	}
	return a;
}
short check(const struct clocks a)
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
	short t;
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

short exist(struct node *head,struct clocks t)
{
	while(head != NULL)
	{
		if(head -> clock.c[0] == t.c[0] &&
		   head -> clock.c[1] == t.c[1] &&
		   head -> clock.c[2] == t.c[2] &&
		   head -> clock.c[3] == t.c[3] &&
		   head -> clock.c[4] == t.c[4] &&
		   head -> clock.c[5] == t.c[5] &&
		   head -> clock.c[6] == t.c[6] &&
		   head -> clock.c[7] == t.c[7] &&
		   head -> clock.c[8] == t.c[8])
		        return 1;
		head = head -> point;
	}
	return 0;
}
#ifdef DEBUG
void out(struct node *head)
{
	int i;	
	for(i = 0;i < 9;i++)
			printf("%hd ",head ->clock .c[i]);
		printf(":");
	while(head -> parent!= NULL)
	{
		
		printf("%hd ",head -> method + 1);
		head = head -> parent;
	}
	putchar(10);
}
#endif