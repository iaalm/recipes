/*
ID: simonin1
LANG: C
TASK:maze1
*/

#include<stdio.h>
#include<stdlib.h>
typedef struct List
{
	int x,y;
	struct List *next;
} list;

int l,h;

int translate(int a,int b)
{
	return (a * l + b);
}

void freelist(list *p)
{
	list* n;
	for(n = p -> next;p != NULL;n = p,p = p -> next)
	        free(p);
}

void add(list **p,int x,int y)
{
	list *t = (list*)malloc(sizeof(list));
	t -> x = x;
	t -> y = y;
	t -> next = * p;
	*p = t;
}

int main()
{
	int i,j,result = 1,un = 1;
	list *o = NULL,*n = NULL,*t;
	char* table;
	
	FILE *fp = fopen("maze1.in","r");
	fscanf(fp,"%d %d",&l,&h);
	l = l * 2 + 1;
	h = h * 2 + 1;
	table = (char*)malloc(sizeof(char) * l * h);
	for(i = 0;i < h;i++)
  	{
		fscanf(fp,"%c",&j);
		for(j = 0;j < l;j++)
		        fscanf(fp,"%c",table + translate(i,j));
	}
	fclose(fp);

	for(i = 0;i < l;i++)
	{
	        if(table[translate(0,i)] == ' ')
	        {
			table[translate(1,i)] = table[translate(0,i)] = 'x';
			add(&n,1,i);
		}
	        if(table[translate(h - 1,i)] == ' ')
	        {
			table[translate(h - 2,i)] = table[translate(h - 1,i)] = 'x';
			add(&n,h - 2,i);
		}
	}
	
	for(i = 0; i < h;i++)
	{
	        if(table[translate(i,0)] == ' ')
	        {
			table[translate(i,1)] = table[translate(i,0)] = 'x';
			add(&n,i,1);
		}
	        if(table[translate(i,l - 1)] == ' ')
	        {
			table[translate(i,l - 2)] = table[translate(i,l - 1)] = 'x';
			add(&n,i,l - 2);
		}
	}
	
 	while(n != NULL)
	{
		free(o);
		o = n;
		n = NULL;
		while(o != NULL)
		{
			i = o -> x;
			j = o -> y;
			if(i != 0 && table[translate(i - 1,j)] == ' ')
			{
                                table[translate(i - 1,j)] = 'x';
                                add(&n,i - 1,j);
			}
			if(i < h && table[translate(i + 1,j)] == ' ')
			{
                                table[translate(i + 1,j)] = 'x';
                                add(&n,i + 1,j);
			}
			if(j != 0 && table[translate(i,j - 1)] == ' ')
			{
                                table[translate(i,j - 1)] = 'x';
                                add(&n,i,j - 1);
			}
			if(j < l && table[translate(i,j + 1)] == ' ')
			{
                                table[translate(i,j + 1)] = 'x';
                                add(&n,i,j + 1);
			}
			o = o -> next;
		}
			/*{
				putchar(10);putchar(10);
				for(i =0;i < h;i++)
				{
					for(j = 0;j < l;j++)
					        printf("%c",table[translate(i,j)]);
					putchar(10);
				}
			}*/
		result++;
	}
	
	fp = fopen("maze1.out","w");
	fprintf(fp,"%d\n",result/2);
	fclose(fp);
	
	free(o);
	free(n);
	
	return 0 ;
}

