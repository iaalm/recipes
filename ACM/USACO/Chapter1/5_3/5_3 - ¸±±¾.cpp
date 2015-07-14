/*
ID: simonin1
LANG: C
TASK:sprime
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int num;
	struct Node *p;
} node;

void freelist(node *head)
{
 	node *p = head;
	while(p != NULL)
	{
		head = head -> p;
		free(p);
		p = head;
	}
}

double sqrt(double number)
{
	if(__builtin_expect(number < 0,0))
		return -1;
	if(__builtin_expect(number == 0,0))
		return 0;
	double pre,next = number/2;
	do
	{
	pre = next;
	next = pre/2+number/pre/2;             //牛顿迭代法 简化式
	}while( abs(pre-next) >= 0.1);
	return next;
}

short check(int n)
{
	if(n == 0 || n == 1)
	        return 0;
	int sq = sqrt(n),i;
	for(i = 2;i <= sq;i++)
	        if(n % i == 0)
	                return 0;
	return 1;
}

int main()
{
	node *head[9],*p,*q;
	int i,j,k,n;
	FILE *fp = fopen("sprime.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);
	
	head[0] = (node*) malloc(sizeof(node));
	head[0] -> num = 0;
	head[0] -> p = NULL;
	
	for(i = 1;i <= n;i++)
	{
		p = head[i - 1];
		head[i] = NULL;
		while(p != NULL)
		{
			for(j = 0;j < 10;j++)
			{
				k = (p -> num) * 10 + j;
			        if(check(k))
			        {
					q = (node*) malloc(sizeof(node));
					q -> num = k;
					q -> p = head[i];
					head[i] = q;
				}
			}
			p = p -> p;
		}
	}
	
	p = head[n];
	fp = fopen("sprime.out","w");
	while(p != NULL)
	{
		fprintf(fp,"%d\n",p -> num);
		p = p -> p;
	}
	fclose(fp);
	
	for(i = 0;i <= n;i++)
	        freelist(head[i]);
	
	return 0;
}
