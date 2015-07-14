/*
ID: simonin1
LANG: C
TASK:sort3
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define min(X,Y) (X<Y)?X:Y;

int main()
{
	int h[3],*m,w12,w13,w21,w23,w31,w32,t,n,result = 0,i;
	h[0] = h[1] = h[2] = 0;
	w12 = w13 = w21 = w23 = w31 = w32 = 0;
	
	FILE *fp = fopen("sort3.in","r");
	fscanf(fp,"%d",&n);
	m = (int*) malloc(sizeof(int) * n);
	for(i = 0;i < n;i++)
	{
		fscanf(fp,"%d",&t);
		m[i] = t;
		h[t - 1]++;
	}
	fclose(fp);

	for(i = 0;i < h[0];i++)
	{
		if(m[i] == 2)
		        w12++;
		else if(m[i] == 3)
		        w13++;
	}
	for(i = h[0];i < h[0] + h[1];i++)
	{
		if(m[i] == 1)
		        w21++;
		else if(m[i] == 3)
		        w23++;
	}
	for(i = h[0] + h[1];i < n;i++)
	{
		if(m[i] == 2)
		        w32++;
		else if(m[i] == 1)
		        w31++;
	}
	
	t = min(w31,w13);
	w31 -= t;
	w13 -= t;
	result += t;
	
	t = min(w21,w12);
	w21 -= t;
	w12 -= t;
	result += t;

	t = min(w32,w23);
	w32 -= t;
	w23 -= t;
	result += t;
	
	result +=((w12 + w13) * 2);
	
	fp = fopen("sort3.out","w");
	fprintf(fp,"%d\n",result);
	fclose(fp);
	
	return 0;
}
