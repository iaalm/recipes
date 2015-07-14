/*
ID: simonin1
LANG: C
TASK:prefix 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Prefix
{
	char w[12];
	struct Prefix *p;
} prefix;

void strmcpy(char *a,char *b,int n)
{
	a[n] = '\0';
	n--;
	while(n >= 0)
	{
		a[n] = b[n];
		n--;
	}
}

unsigned int used[6250] = {0},now = 0;

int check(char *a,prefix *pre);

int main()
{
	unsigned int i;
	int j,k;
	char t[12],*word = (char*)malloc(sizeof(char) * 200000);
	prefix *p,*pre[10] = {NULL};

	FILE *fp = fopen("prefix.in","r");
	fscanf(fp,"%s",t);
	while(strcmp(t,"."))
	{
		i = strlen(t) - 1;
		p = (prefix*) malloc (sizeof(prefix));
		p -> p = pre[i];
		pre[i] = p;
		strcpy(p -> w,t);
		fscanf(fp,"%s",t);
	}
	
	do
	{
		fscanf(fp,"%s",word + strlen(word));
	}while(!feof(fp));
	fclose(fp);

	while(word[now] != '\0')
	{
		for(i = 0;i < 10;i++)
		{
			if(now >= i && (now - i == 0 || (used[(now - i - 1) >> 5] & (1 << ((now - i - 1) % 32)))))
			{
				if(check(word + now - i,pre[i]))
					break;
			}
		}
		now++;
	}

	fp = fopen("prefix.out","w");
	for(k = 6249;k >= 0;k--)
	{
		if(used[k] != 0)
		{
			for(j = 31;j >= 0;j--)
			{
				if((used[k] & (1 << j)))
				{
					fprintf(fp,"%d\n",(k << 5) + j + 1);
					fclose(fp);
					exit(0);
				}
			}
		}
	}
	fprintf(fp,"%d\n",0);
	fclose(fp);
	
	return 0;
}

int check(char *a,prefix *pre)
{
	int i;
	while(pre != NULL)
	{
		for(i = 0;1;i++)
		{
			if(pre -> w[i] == '\0')
			{
				printf("%d:%s\n",now,pre -> w);
				used[now >> 5] |= (1 << (now % 32));
				return 1;
			}
			if(a[i] == '\0')
				return 1;
			if(a[i] != pre -> w[i])
				break;
		}
		pre = pre -> p;
	}
	return 0;
}
