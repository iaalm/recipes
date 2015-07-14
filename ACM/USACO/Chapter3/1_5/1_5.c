/*
ID: simonin1
LANG: C
TASK: contact
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct list
{
	char s[15];
	struct list* p;
};

char str[250000];
struct list* v = NULL,*lp;

inline int nu(int e,int len)
{
	int n = 0;
	while(len--)
	{
		n <<= 1;
		if(str[e - len] == '1')
			n++;
	}
	return n;
}

void freelist()
{
	lp = v;
	while(v != NULL)
	{
		v = v -> p;
		free(lp);
		lp = v;
	}
}

void ins(int i,int j)
{
	lp = v;
	v = (struct list*)malloc(sizeof(struct list));
	v -> p = lp;
	v -> s[i] = '\0';
	int k;
	while(i --)
	{
		if(j & 1)
			v -> s[i] = '1';
		else
			v -> s[i] = '0';
		j >>= 1;
	}

}


int main()
{
	int a,b,n,i = 0,j,k,l,o,len,*result[15];
	char LF;
	FILE *fp = fopen("contact.in","r");
	fscanf(fp,"%d %d %d",&a,&b,&n);
	fgetc(fp);
	while(fscanf(fp,"%s",str + i) != EOF)
		i += 80;
	len = i - 80 + strlen(str + i - 80 );
	fclose(fp);

	for(i = a;i <= b;i++)
	{
		result[i] = (int*)malloc((j = pow(2,i) * sizeof(int)));
		bzero(result[i],j);

		for(j = i - 1;j < len;j++)
			result[i][nu(j,i)]++;
	}

	fp = fopen("contact.out","w");
	len = 100000;
	while(n--)
	{
		k = 0;
		for(i = b,l = pow(2,i);i >= a;i--,l = pow(2,i))
			for(j = l - 1;j >= 0;j--)
			{
				if(result[i][j] > k && result[i][j] < len)
				{
					k = result[i][j];
					freelist();
					ins(i,j);
				}
				else if(result[i][j] == k)
				{
					ins(i,j);
				}
			}
		if(k == 0)
			break;
		else
		{
			len = k;
			LF = ' ';
			fprintf(fp,"%d\n%s",k,v -> s);
			lp = v;
			v = v -> p;
			free(lp);
			o = 1;
			while(v != NULL)
			{
				fprintf(fp,"%c%s",LF,v -> s);
				LF = ' ';
				lp = v;
				v = v -> p;
				free(lp);
				if(++o % 6 == 0)
					LF = '\n';

			}
			fputc(10,fp);

		}
	}
	fclose(fp);
	return 0;
}
