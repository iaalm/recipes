/*
ID: simonin1
LANG: C
TASK:fracdec
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct NODE
{
	int mod;
	char num;
	struct NODE* p;
} node;

int acc;
FILE *fp;

inline void print(char t);

int main()
{
	unsigned short exist[100000] ={0};
	int pre,next,i;
	node head = {0,0,NULL},*t,*p = &head,*loop = NULL;
	fp = fopen("fracdec.in","r");
	fscanf(fp,"%d %d",&pre,&next);
	fclose(fp);
	
	fp = fopen("fracdec.out","w");
	i = pre / next;
	fprintf(fp,"%d.",i);
	pre %= next;
	
	acc = 1;
	do
	{
		i /= 10;
		acc++;
	}while(i != 0);
	
	if(pre % next == 0)
	        fprintf(fp,"0\n",i);
	        
	else
	{
		while(1)
		{
			pre *= 10;
			t = (node*)malloc(sizeof(node));
			t -> mod = pre % next;
			t -> num = pre / next;
			pre = t -> mod;
			t -> p = NULL;
			if(t -> mod == 0)
				break;

			//search
			if(exist[t -> mod] & (1 << (t -> num)))
			{
				for(loop = head.p;loop != NULL;loop = loop -> p)
				        if(loop -> mod == t -> mod && loop -> num == t -> num)
				                break;
				        break;
			}

			exist[t -> mod] |= (1 << (t -> num));

			p -> p = t;
			p = t;
		}

		p = head.p;
		while(p != loop)
		{
			print(p -> num + '0');
			p = p -> p;
		}
		if(loop != NULL)
		{
			print('(');
			while(loop != NULL)
			{
				print(loop -> num + '0');
				loop = loop -> p;
			}
			print(')');
		}
		else
		        print(t -> num + '0');
		fprintf(fp,"\n");
		free(t);
	}
	fclose(fp);

	for(p = head.p;p != NULL;p = t)
	{
		t = p -> p;
		free(p);
	}
	
	return 0;
}

void print(char t)
{
	if(acc == 76)
	{
	        fprintf(fp,"\n");
	        acc = 0;
	}
	fprintf(fp,"%c",t);
	acc++;
}
