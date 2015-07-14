#include<stdio.h>
#include<string.h>

void correct(int* t);

int main()
{
	int t,xl,al,bl,i,jj,result[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char x[20],a[20],b[20];
	scanf("%d",&t);
	while(t != 0)
	{
		jj = 0;
		scanf("%s %s %s",x,a,b);
		xl = strlen(x);
		al = strlen(a);
		bl = strlen(b);
		for(i = 1 + xl;i <= bl;i++)
		{
			if(i > al)
			{
				if(b[bl - i] - '0' >= jj)
				{
					result[bl -i] = b[bl -i] - '0' -jj;
					jj = 0;
				}
				else
				{
					result[bl -i] = b[bl -i] + 10 - '0' -jj;
					jj = 1;
				}
				continue;
			}
			if(b[bl - i] >= a[al - i] + jj)
			{
				result[bl - i] = b[bl - i] - a[al - i] - jj;
				jj = 0;
			}
			else
			{
				result[bl - i] = b[bl - i] + 10 - a[al - i] - jj;
				jj = 1;
			}
		}
		jj = 0;
		if(xl > al)
			jj = 1;
		for(i = xl;i > 0&&jj == 0;i--)
		{
			if(x[xl - i] > a[al -i])
			{
				jj = 1;
				break;
			}
			if(x[xl - i] < a[al -i])
			{
				jj = -1;
				break;
			}
		}
		if(jj == -1)
		{
			result[bl - xl - 1]--;
		}
		if(xl > bl)
		{
			printf("0\n");
			continue;
		}
		for(i = xl;i > 0&&jj == 0;i--)
		{
			if(x[xl - i] > b[bl -i])
			{
				jj = 1;
				break;
			}
			if(x[xl - i] < b[bl -i])
			{
				jj = -1;
				break;
			}
		}
		if(jj != -1)
			result[bl - xl - 1]++;
		correct(result + bl -xl - 1);
		i = 0;
		while(b[i] == 0)
		{
			i++;
		}
		while(i < bl -xl)
			printf("%d",b[i]);
		for(i = 0;i < bl - xl;i++)
			if(result[i] != 0)
				break;
		if(i == bl -xl)
			putchar('0');
		putchar(10);
		t--;
	}
	return 0;
}


void correct(int* t)
{
	if(*t >= 10)
	{
		*t -= 10;
		t--;
		(*t)++;
		correct(t);
	}
	if(t < 0)
	{
		*t += 10;
		t--;
		(*t)--;
		correct(t);
	}
}
