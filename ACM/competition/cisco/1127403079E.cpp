#include<stdio.h>
#include<stdlib.h>

#define TRAN(X,Y) ((X) * w + (Y))

int w,h;
char *map;
int fn(int i, int j);

int main()
{
	int max,i,j,t;
	while(scanf("%d",&w) != EOF)
	{
		max = 0;
		scanf("%d",&h);
		map = (char*)malloc(sizeof(char) * w * h);

		for(i = 0;i < h;i++)
		{
			getchar();
			for(j = 0;j < w;j++)
			{
				scanf("%c",map + TRAN(i,j));
			}
		}
		//开始计算
		for(i = 0;i < h;i++)
			for(j = 0;j < w;j++)
				if(map[TRAN(i,j)] == '*')
				{
					t = fn(i,j);
					if(t > max)
						max = t;
				}
		printf("%d\n",max);

	}
	return 0;
}

int fn(int i, int j)
{
	int result = 1;
	map[TRAN(i,j)] = '.';				//使得每个联通块只被计算一次

	if(i > 0 && map[TRAN(i - 1,j)] == '*')
		result += fn(i - 1,j);
	if(i < h - 1 && map[TRAN(i + 1,j)] == '*')
		result += fn(i + 1,j);
	if(j > 0 && map[TRAN(i,j - 1)] == '*')
		result += fn(i,j - 1);
	if(j < w - 1 && map[TRAN(i,j + 1)] == '*')
		result += fn(i,j + 1);
	return result;
}