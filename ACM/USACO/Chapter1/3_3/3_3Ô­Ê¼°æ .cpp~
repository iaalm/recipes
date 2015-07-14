/*
ID: simonin1
LANG: C
TASK: calfflac
*/

#include<stdio.h>
#define DEBUG
#define M 2100

char filter(char in);
int check(char* a,int j);

int main()
{
	char a[M],t;
	int length = 0,i,j,begin = 0,end = 0,l = 0,tl;
	FILE *fp = fopen("calfflac.in","r");
	do
	{
		a[length] = fgetc(fp);
		length++;
	}while(!feof(fp));
	fclose(fp);

	length--;
	for(i = 0;i < length;i++)
	{
		if((t = filter(a[i])) == 30)
			continue;
		for(j = length;j > i;j--)
		{
			if(t == filter(a[j]))
			{
				if(tl = check(a + i + 1,j - i - 1))
				{
					printf("%d %d tl:%d\n",i,j,tl);
					if(tl > l)
					{
						l = tl;
						end = j;
						begin = i;
					}
					i++;
					break;
				}
			}
		}
	}

	fp = fopen("calfflac.out","w");
	fprintf(fp,"%d\n",l);
	for(i = begin;i <= end;i++)
		fprintf(fp,"%c",a[i]);
	fprintf(fp,"\n");
	fclose(fp);

	return 0;
}

char filter(char in)
{
	if(in >= 'a' && in <= 'z')
		return (in - 'a');
	else if(in >= 'A' && in <= 'Z')
		return (in - 'A');
	else
		return 30;
}

int check(char* a,int j)
{
	int i = 0,result = 2;
	char p,q;
	j--;
	do
	{
		if((p = filter(a[i])) == 30)
		{
			i++;
			continue;
		}
		if((q = filter(a[j])) == 30)
		{
			j--;
			continue;
		}
		if(p == q)
		{
			result += 2;
			if(i == j)
				result--;
		}
		else
			return 0;
		i++;
		j--;
	}while(i <= j);
	return result;
}
