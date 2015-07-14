/*
ID: simonin1
LANG: C
TASK: packrec
*/

#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef struct
{
	int x;
	int y;
	int lx;
	int ly;
	int angle;
} block;

typedef struct List
{
	int x;
	int y;
	int max;
	List *point;
} mylist;

void work(block *b);
int check(block *b,int i);
mylist* area(block *b);
void sort(mylist* head);
void freemylist(mylist *head);
int max = 10000;
mylist *head = NULL;

int main()
{
	block b[N];
	mylist *t;
	int i,j;
	FILE *fp = fopen("packrec.in","r");
	for(i = 0;i < N;i++)
	{
		fscanf(fp,"%d %d",&b[i].lx,&b[i].ly);
		b[i].angle = 0;
	}
	fclose(fp);
	
	for(i = 0;i < N;i++)
	{
		for(j = 0;j < N;j++)
		{
			b[i].angle = 0;
		}
		b[i].x = 0;
		b[i].y = 0;
		b[i].angle = 1;
		work(b);
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
	freemylist(head);
	
	return 0;
}
void work(block *b)
{
        mylist *t;
        int filled = 1,i,j,k;
        for(i = 0;i < N;i++)
        {
		if(b[i].angle == 0)
		{
			filled = 0;
			for(j = 1;j < 9;j++)
			{
				b[i].angle = j;
				for(k =  0;k < N;k++)
				{
					if(i == k||b[k].angle == 0)
					        continue;
					b[i].x = b[k].x;
					b[i].y = b[k].y;
					if(check(b,i))
					{
						work(b);
					}
					else
					{
						continue;
					}
					b[i].x = b[k].x + b[k].lx;  //////////////////////
					b[i].y = b[k].y;
					if(check(b,i))
					{
						work(b);
					}
					else
					{
						continue;
					}
					b[i].x = b[k].x;
					b[i].y = b[k].y + b[k].ly;
					if(check(b,i))
					{
						work(b);
					}
					else
					{
						continue;
					}
					b[i].x = b[k].x + b[k].lx;
					b[i].y = b[k].y + b[k].ly;
					if(check(b,i))
					{
						work(b);
					}
					else
					{
						continue;
					}
				}
			}
			b[i].angle = 0;
		}
	}
	if(filled == 1)
	{
                
		if((j = (t = area(b)) -> max) == max)
		{
			t -> point = head;
			head = t;
		}
		else if(j < max)
		{
			max = j;
			freemylist(head);
			head = t;
			t -> point = NULL;
		}
		else
		        free(t);
	}
}

int check(block *b,int i) //任务艰巨
{
	if(b[i].x = 0 && 3 >= b[i].angle && 6 <= b[i].angle)
		return 0;
	if(b[i].y = 0 && 5 >= b[i].angle && 8 <= b[i].angle)
		return 0;
	int x1,x2,y1,y2,m1,m2,n1,n2;
	switch(b[i].angle)
	{
		case 1:x1 = b[i].x;x2 = x1 + b[i].lx;y1 = b[i].y;y2 = y1 + b[i].ly;break;
		case 2:x1 = b[i].x;x2 = x1 + b[i].ly;y1 = b[i].y;y2 = y1 + b[i].lx;break;
		case 3:x1 = b[i].x;x2 = x1 - b[i].ly;y1 = b[i].y;y2 = y1 + b[i].lx;break;
		case 4:x1 = b[i].x;x2 = x1 - b[i].lx;y1 = b[i].y;y2 = y1 + b[i].ly;break;
		case 5:x1 = b[i].x;x2 = x1 - b[i].lx;y1 = b[i].y;y2 = y1 - b[i].ly;break;
		case 6:x1 = b[i].x;x2 = x1 - b[i].ly;y1 = b[i].y;y2 = y1 - b[i].lx;break;
		case 7:x1 = b[i].x;x2 = x1 + b[i].ly;y1 = b[i].y;y2 = y1 - b[i].lx;break;
		case 8:x1 = b[i].x;x2 = x1 + b[i].lx;y1 = b[i].y;y2 = y1 - b[i].ly;break;
	}
	if(x1 > x2)
	{
		x1 +=x2;
		x2 = x1 - x2;
		x1 = x1 - x2;
	}
	if(y1 > y2)
	{
		y1 +=y2;
		y2 = y1 - y2;
		y1 = y1 - y2;
	}
	int j;
	for(j = 0;j < N;j++)
	{
		if(i == j)
		{
			continue;
		}
		else
		{
                        switch(b[j].angle)
                        {
				case 1:m1 = b[j].x;m2 = m1 + b[j].lx;n1 = b[j].y;n2 = n1 + b[j].ly;break;
				case 2:m1 = b[j].x;m2 = m1 + b[j].ly;n1 = b[j].y;n2 = n1 + b[j].lx;break;
				case 3:m1 = b[j].x;m2 = m1 - b[j].ly;n1 = b[j].y;n2 = n1 + b[j].lx;break;
				case 4:m1 = b[j].x;m2 = m1 - b[j].lx;n1 = b[j].y;n2 = n1 + b[j].ly;break;
				case 5:m1 = b[j].x;m2 = m1 - b[j].lx;n1 = b[j].y;n2 = n1 - b[j].ly;break;
				case 6:m1 = b[j].x;m2 = m1 - b[j].ly;n1 = b[j].y;n2 = n1 - b[j].lx;break;
				case 7:m1 = b[j].x;m2 = m1 + b[j].ly;n1 = b[j].y;n2 = n1 - b[j].lx;break;
				case 8:m1 = b[j].x;m2 = m1 + b[j].lx;n1 = b[j].y;n2 = n1 - b[j].ly;break;
			}
			if(m1 > m2)
			{
				m1 +=m2;
				m2 = m1 - m2;
				m1 = m1 - m2;
			}
			if(n1 > n2)
			{
				n1 +=n2;
				n2 = n1 - n2;
				n1 = n1 - n2;
			}
			if((m1 > x1 && m1 < x2)||(m2 > x1 && m2 < x2)||(n1 > y1 && n1 < y2)||(n2 > y1 && n2 < y2))
			        return 0;
		}
	}
	return 1;
}

mylist* area(block *b)
{
	int i;
	mylist *p = (mylist*)malloc(sizeof(mylist));
	p -> x = 0;
	p -> y = 0;
	for(i = 0;i < N;i++)
	{
		if(b[i].x > p -> x)
			p -> x = b[i].x;
                if(b[i].y > p -> y)
			p -> y = b[i].y;
	}
	if(p -> x > p -> y)
	{
                p -> x += p -> y;
                p -> y= p -> x - p -> y;
                p -> x = p -> x - p -> y;
	}
	p -> max = p -> x * p -> y;
	return p;
}

void sort(mylist* head)                  //若作为库,需大幅改进
{
	mylist *p,*q,*minindex,t;
	p = head;
	while(p -> point != NULL)
	{
		p = p -> point;
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
			t = *p;
			*p = *minindex;
			*minindex = t;
		}
	}
}

void freemylist(mylist *head)
{
	mylist *p = head;
	while(p != NULL)
	{
		head = head -> point;
		free(p);
		p = head;
	}
}
