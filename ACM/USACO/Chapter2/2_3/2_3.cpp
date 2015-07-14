/*
ID: simonin1
LANG: C
TASK:runround
*/

#include<stdio.h>

struct num
{
	short num:15;
	short used:1;
};

void add(struct num *a);
int check(struct num *a);

int length = 0;

int main()
{
	struct num m[16];
	int n,i,unfinish = 1;
	for(n = 0;n < 16;n++)
		m[n].num = -1;
	FILE *fp = fopen("runround.in","r");
	fscanf(fp,"%d",&n);
	fclose(fp);

	while(n != 0)
	{
		m[length].num = n % 10;
		length++;
		n /= 10;
	}

	do
	{
		add(m);
		if(check(m))
		        continue;
		for(n = 0;n < length;n++)
			m[n].used = 0;
		n = length - 1;
		for(i = 0;i < length;i++)
		{
			if(m[n].used == 1)
				break;
			m[n].used = 1;
			n -= m[n].num;
			while(n < 0)
				n += length;
		}

		unfinish = 0;
		if(n != length - 1)
			unfinish = 1;
		for(i = 0;i < length;i++)
			if(m[i].used == 0)
				unfinish = 1;
	}while(unfinish);
	fp = fopen("runround.out","w");
	for(n = length - 1;n >= 0;n--)
		fprintf(fp,"%hd",m[n].num);
	fprintf(fp,"\n");
	fclose(fp);

	return 0;
}

void add(struct num *a)
{
	if(a -> num == -1)
	{
		a -> num = 1;
		length++;
		return;
	}
	a -> num++;
	if(a -> num == 10)
	{
		a -> num = 0;
		add(a + 1);
	}	
}

int check(struct num *a)
{
	int i,j;
	for(i = 0;i < length;i++)
	        for(j = i + 1;j < length;j++)
	                if(a[i].num == a[j].num)
	                        return 1;
	return 0;
}
