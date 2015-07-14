/*
ID: simonin1
LANG: C
TASK: calfflac
*/

#include<stdio.h>
#include<stdlib.h>
#define M 20010
#define N 2001

char filter(char in)
{
	if(in >= 'a' && in <= 'z')
		return (in - 'a');
	else if(in >= 'A' && in <= 'Z')
		return (in - 'A');
	else
		return 30;
}

int main()
{
	FILE *fp;
	char *a = (char*)malloc(sizeof(char) * M),p,q;
	int result = 0,i,k,j,begin,end,t,length = 0;
	
	fp = fopen("calfflac.in","r");
	do
	{
		a[length] = fgetc(fp);
		length++;
	}while(!feof(fp));
	fclose(fp);
	
	for(i = 0;i < length;i++)
	{
		if(filter(a[i]) == 30)
			continue;
		j = i - 1;
		k = i + 1;
		t = 1;
		while(i - j < N && k - i < N && j >= 0 && k < length)
		{
			if((p = filter(a[j])) == 30)
			{
				j--;
				continue;
			}
			if((q = filter(a[k])) == 30)
			{
				k++;
				continue;
			}
			if(p == q)
			{
				t += 2;
			}
			else
				break;
			j--;
			k++;
		}
		if(t > result)
		{
			result = t;
			begin = j + 1;
			while(filter(a[begin]) == 30)
				begin++;
			end = k - 1;
			while(filter(a[end]) == 30)
				end--;
			//printf("%d %d\n",begin,end);
		} 
		
		j = i;
		k = i + 1;
		t = 0;
		while(i - j < N && k - i < N && j >= 0 && k < length)
		{
			if((p = filter(a[j])) == 30)
			{
				j--;
				continue;
			}
			if((q = filter(a[k])) == 30)
			{
				k++;
				continue;
			}
			if(p == q)
			{
				t += 2;
			}
			else
				break;
			j--;
			k++;
		}
		if(t > result)
		{
			result = t;
			begin = j + 1;
			while(filter(a[begin]) == 30)
				begin++;
			end = k - 1;
			while(filter(a[end]) == 30)
				end--;
			//printf("%d %d\n",begin,end);
		} 
	}
	
	fp = fopen("calfflac.out","w");
	fprintf(fp,"%d\n",result);
	for(i = begin;i <= end;i++)
		fprintf(fp,"%c",a[i]);
	fprintf(fp,"\n");
	fclose(fp);

	return 0;
}
