#include<stdio.h>
#include<stdlib.h>

#define TRAN(X,Y) ((X) * y + (Y))

int x,y;
char* mar;

long long check(int cx,int cy);

int main()
{
	int i,j,cx,cy;
	long long result;
	while(1)
	{
		scanf("%d %d %d %d",&x,&y,&cx,&cy);
		if(x == 0)
			break;
		cx--;
		cy--;
		mar = (char*) malloc(sizeof(char) * x * y);
		for(i = 0;i < x;i++)
		{
			getchar();
			for(j = 0; j < y;j++)
				scanf("%c",mar + TRAN(i,j));
		}

		result = check(cx,cy) * 4;

		for(i = 0;i < x;i++)
			for(j = 0; j < y;j++)
			{
				if(mar[TRAN(i,j)] == '1')
				{
					//mar[TRAN(i,j)] = '2';
					if(i > 0 && mar[TRAN(i - 1,j)] == '1')
						result--;
					if(i < x - 1 && mar[TRAN(i + 1,j)] == '1')
						result--;
					if(j > 0 && mar[TRAN(i,j - 1)] == '1')
						result--;
					if(j < y - 1 && mar[TRAN(i,j + 1)] == '1')
						result--;
				}
			}

		printf("%lld\n",result);
		free(mar);
	}
	return 0;
}

long long check(int cx,int cy)
{
	long long result = 1;
	if(cx < 0 || cx >= x || cy < 0 || cy >= y || mar[TRAN(cx,cy)] != 'X')
		return 0;
	mar[TRAN(cx,cy)] = '1';
	result += check(cx - 1,cy - 1);
	result += check(cx - 1,cy);
	result += check(cx - 1,cy + 1);
	result += check(cx,cy - 1);
	result += check(cx,cy + 1);
	result += check(cx + 1,cy - 1);
	result += check(cx + 1,cy);
	result += check(cx + 1,cy + 1);
	return result;
}
