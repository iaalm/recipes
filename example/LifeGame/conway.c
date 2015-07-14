#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define X 30
#define Y 90
#define T(x,y) ((x)*Y+(y))
int main()
{
	const char setx[8] = { 0, 0,-1,-1,-1, 1, 1, 1},
      	  	   sety[8] = { 1,-1,-1, 0, 1,-1, 0, 1};
	short *a,*b,*pc;
	int i,j,k,x,y,c;
	char t;
	a = (short*) malloc (sizeof(short) * X * Y);
	b = (short*) malloc (sizeof(short) * X * Y);
	pc = a;
	srand((unsigned) time(0));
	for(i = 0;i < X;i++)
		for(j = 0;j < Y;j++)
			b[T(i,j)] = rand() % 2;
	do
	{
		for(i = 0;i < X;i++)
			for(j = 0;j < Y;j++)
			{
				c = 0;
				for(k = 0;k < 8;k++)
				{
					x = setx[k] + i;
					y = sety[k] + j;
					if(x >= 0 && x < X && y >= 0 && y< Y && b[T(x,y)])
						c++;
				}
				if(c < 2 || c > 3)
					a[T(i,j)] = 0;
				else if(c == 3)
					a[T(i,j)] = 1;
				else
					a[T(i,j)] = b[T(i,j)];
			}
		for(i = 0;i < X;i++)
		{
			for(j = 0;j < Y;j++)
				putchar(a[T(i,j)]?'*':' ');
			putchar(10);
		}
		putchar(10);
		pc = a;
		a = b;
		b = pc;
	}while(getchar() != 'q');
	return 0;
}
