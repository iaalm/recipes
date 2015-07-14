/*
ID: simonin1
LANG: C
TASK:pprime
*/

#include<stdio.h>
#include<stdlib.h>

#define N 4

typedef struct Node
{
	int num;
	struct Node *p;
} node;

node *sing = NULL,*doub = NULL;
int min,max;

short check(int n);
short creats(char *c);                //ÊÇ·ñ¹ý´ó,Õý³£·µ»Ø0
short creatd(char *c);

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
	next = pre/2+number/pre/2;             //ç‰›é¡¿è¿­ä»£æ³• ç®€åŒ–å¼
	}while( abs(pre-next) >= 0.1);
	return next;
}

int main()
{
	node *head = NULL,*t;
	char c[N];
	FILE *fp = fopen("pprime.in","r");
	fscanf(fp,"%d %d",&min,&max);
	fclose(fp);
	
	for(c[0] = 0;c[0] <= 9;c[0]++)
	        for(c[1] = 0;c[1] <= 9;c[1]++)
	                for(c[2] = 0;c[2] <= 9;c[2]++)
	                        for(c[3] = 0;c[3] <= 9;c[3]++)
	                                if(creats(c))
	                                        goto sf;
	sf:
        for(c[0] = 0;c[0] <= 9;c[0]++)
	        for(c[1] = 0;c[1] <= 9;c[1]++)
	                for(c[2] = 0;c[2] <= 9;c[2]++)
	                        for(c[3] = 0;c[3] <= 9;c[3]++)
	                                if(creatd(c))
	                                        goto df;
	df:



	while(sing != NULL || doub != NULL)
	{
		if(doub == NULL || (sing != NULL && sing -> num > doub -> num))
		{
			t = sing -> p;
			sing ->p = head;
			head = sing;
			sing = t;
		}
		else
		{
			t = doub -> p;
                        doub ->p = head;
			head = doub;
			doub = t;
		}
	}
	
	fp = fopen("pprime.out","w");
	while(head != NULL)
	{
		t = head;
		fprintf(fp,"%d\n",head -> num);
		head = head -> p;
		free(t);
	}
	fclose(fp);
	
	return 0;
}

short creats(char *c)
{
	int n;
	node *t;
	if(c[0] != 0)
	{
		n = c[0] * 1000001 + c[1] * 100010 + c[2] * 10100 + c[3] * 1000;
	}
	else
	{
		if(c[1] != 0)
		{
			n = c[1] * 10001 + c[2] * 1010 + c[3] * 100;
		}
		else
		{
			if(c[2] != 0)
			{
				n = c[2] * 101 + c[3] * 10;
			}
			else
			{
				if(c[3] != 0)
				{
					n = c[3];
				}
				else
				        n = 0;
			}
		}
	}
	if(n < min)
	        return 0;
	else if(n > max)
	        return 1;
	else
		if(check(n))
		{
			t = (node*) malloc(sizeof(node));
			t -> num = n;
			t -> p = sing;
			sing = t;
		}
	return 0;
}

short creatd(char *c)
{
	int n;
	node *t;
	if(c[0] != 0)
	{
		n = c[0] * 10000001 + c[1] * 1000010 + c[2] * 100100 + c[3] *11000;
	}
	else
	{
		if(c[1] != 0)
		{
			n = c[1] * 100001 + c[2] * 10010 + c[3] *1100;
		}
		else
		{
			if(c[2] != 0)
			{
				n = c[2] * 1001 + c[3] * 110;
			}
			else
			{
				if(c[3] != 0)
				{
					n = c[3] * 11;
				}
				else
				        n = 0;
			}
		}
	}
	if(n < min)
	        return 0;
	else if(n > max)
	        return 1;
	else
		if(check(n))
		{
			t = (node*) malloc(sizeof(node));
			t -> num = n;
			t -> p = doub;
			doub = t;
		}
	return 0;
}

short check(int n)
{
	int sq = sqrt(n),i;
	for(i = 2;i <= sq;i++)
	        if(n % i == 0)
	                return 0;
	 return 1;
}
