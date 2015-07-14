/*
ID: simonin1
LANG: C
TASK: calfflac
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define DEBUG
#define M 21000

inline char filter(char in);
int check(char* a,int length);

int main()
{
	char *a = (char*)malloc(sizeof(char) * M),t;
	assert(a);
	int length = 0,i,j,begin = 0,end = 0,l = 2,tl;
	FILE *fp = fopen("calfflac.in","r");
	do
	{
		a[length] = fgetc(fp);
		length++;
	}while(!feof(fp));
	fclose(fp);
	
	
	length--;
	for(i = 0;i < length - l;i++)
	{
		if(i % 1000 == 0)
		printf("%d\n",i);
		if((t = filter(a[i])) == 30)
			continue;
		for(j = (length < (i + 2001)?length:(i + 2001));j > (i + l);j--)
		{
			if(t == filter(a[j]))
			{
				if((tl = check(a + i + 1,j - i - 1)) > l)
    				{
					l = tl;
					end = j;
					begin = i;
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

inline char filter(char in)
{
	if(in >= 'a' && in <= 'z')
		return (in - 'a');
	else if(in >= 'A' && in <= 'Z')
		return (in - 'A');
	else
		return 30;
}

int check(char* a,int length)
{

	int i = length / 2,j = (length + 1) / 2,result = 2;
	char p,q;
	do
	{
		if((p = filter(a[i])) == 30)
		{
			i--;
			continue;
		}
		if((q = filter(a[j])) == 30)
		{
			j++;
			continue;
		}
		if(p == q)
		{
			result += 2;
		}
		else
		{
			return 0;
			break;
		}
		i--;
		j++;
	}while(i > 0 && j < length);
	if(i == j)
		result++;
	return result;
}
