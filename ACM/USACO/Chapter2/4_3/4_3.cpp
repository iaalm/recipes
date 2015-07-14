/*
ID: simonin1
LANG: C
TASK:cowtour
*/

#include<stdio.h>
#include<math.h>
#define MAX 150
typedef struct
{
	int x,y;
	double d[MAX];
} nod;

int n;
double result = 1e10;
nod node[MAX];

inline double dis(int i,int j);
void link(int m,int nin);

void print()
{
	int i,j;
        for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			printf("%15.5lf|",node[i].d[j] == 1e10?0:node[i].d[j]);
		putchar(10);
	}
	putchar(10);
}

int main()
{
	int i,j,p,q;
	double max,t,d;
	char temp;
	FILE *fp = fopen("cowtour.in","r");
	fscanf(fp,"%d",&n);
	for(i = 0;i < n;i++)
		fscanf(fp,"%d %d",&node[i].x,&node[i].y);
	for(i = 0;i < n;i++)
	{
		fscanf(fp,"%c",&temp);
		for(j = 0;j < n;j++)
		{
			fscanf(fp,"%c",&temp);
			if(temp == '1')
				node[i].d[j] = 1;
			else
				node[i].d[j] = 1e10;
		}
	}
	fclose(fp);

/*print();direct*/
	for(i = 0;i < n;i++)
	node[i].d[i] = 0;
	
	for(i = 0;i < n;i++)
		for(j = i + 1;j < n;j++)
			if(node[i].d[j] == 1)
				node[i].d[j] = node[j].d[i] = dis(i,j);
/*print();linked*/
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			if(node[i].d[j] != 1e10)
				link(i,j);
//in
        for(i = 0;i < n;i++)
		for(j = i + 1;j < n;j++)
		if(node[i].d[j] != 1e10 && node[i].d[j] > result)
		        result = node[i].d[j];
/*print();start*/
	for(p = 0;p < n;p++)
		for(q = n - 1;q > p;q--)
		{
			if(node[p].d[q] == 1e10)
			{
				d = dis(p,q);
				max = 0;
				for(i = 0;i < n;i++)
					for(j = n - 1;j > i;j--)
					{
						if(node[p].d[i] != 1e10 && node[q].d[j] != 1e10)
							t = node[i].d[p] + d + node[q].d[j];
						else if(node[q].d[i] != 1e10 && node[p].d[j] != 1e10)
							t = node[i].d[q] + d + node[p].d[j];
						else
                    					continue;
						if(t > max)
							max = t;
						if(max >= result)
						        goto again;
					}
				if(max < result)
					result = max;
				again:;
			}
		}
	//in
        for(i = 0;i < n;i++)
		for(j = i + 1;j < n;j++)
		if(node[i].d[j] != 1e10 && node[i].d[j] > result)
		        result = node[i].d[j];

	fp = fopen("cowtour.out","w");
	fprintf(fp,"%lf\n",result);
	fclose(fp);

	return 0;
}

void link(int m,int nin)
{
	int i;
	for(i = 0;i < n;i++)
	{
		if(node[nin].d[i] != 1e10 && node[m].d[i] > node[m].d[nin] + node[nin].d[i])
		{
			node[m].d[i] = node[i].d[m] = node[m].d[nin] + node[nin].d[i];
			//if(m == 0)printf("%4d %4d:%lf\n",m,i,node[m].d[i]);
			link(m,i);
		}
	}
}

double dis(int i,int j)
{
	return sqrt((node[i].x - node[j].x) * (node[i].x - node[j].x) + (node[i].y - node[j].y) * (node[i].y - node[j].y));
}
