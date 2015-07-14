/*
ID: simonin1
LANG: C
TASK:inflate
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int time,point;
	double tp;
	struct Node* p;
} node;

int best;
int *list;

void work(node* head,int time,int point);
void print(node *head);

int main()
{
	node head={100000,0,1000000,NULL},*t,*p;
	int ttime,num;
	best = 0;
	FILE * fp = fopen("inflate.in","r");
	for(fscanf(fp,"%d %d",&ttime,&num);num > 0;num--)
	{
		t = (node*)malloc(sizeof(node));
		fscanf(fp,"%d %d",&(t -> point),&(t -> time));
		t -> tp = t -> point / (double)t -> time;
		for(p = &head;p -> p != NULL && (p-> p -> tp > t -> tp);p = p -> p);
		t -> p = p -> p;
		p -> p = t;
	}
	fclose(fp);
	list = (int*)malloc(sizeof(int) * ttime);
	for(best = 0;best < ttime;best++)
		list[best] = 0;
	print(&head);
	work(head.p,ttime,0);
	
	fp = fopen("inflate.out","w");
	fprintf(fp,"%d\n",best);
	fclose(fp);
	
	return 0;
}

void work(node* head,int time,int point)
{
	while(head != NULL)
	{
		if(head -> tp * time + point <= best || (list[time] != 0 && point + list[time] <= best))
		        return;
		if(head -> time <= time)
		        work(head,time - head -> time,point + head -> point);
		else if(point > best)
		{
		        best = point;
		        printf("%d\r",best);
		}
		head = head -> p;
	}
	if(best - point > list[time])
	        list[time] = best - point;
}

void print(node *head)
{
	while(head != NULL)
	{
		printf("%d %d %lf\n",head -> point,head -> time,head -> tp);
		head = head -> p;
	}
}
