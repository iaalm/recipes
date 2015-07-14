#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#define clr(X) memset(X,0xff,sizeof(X))
#define INF (1<<26)
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

struct en
{
	char str[80];
	int page[10];
	//==
} ent[120];
int pri[120],pnow,snow;

inline char is(char t)
{
	return t < 'a'?t + 'a' - 'A':t;
}

inline int sc(char *a,char* b)
{
	int i = 0,m,n;
	do
	{
		m = is(a[i]);
		n = is(b[i]);
		if(m < n)
			return -1;
		if(m > n)
			return 1;
	}while(a[++i] != '\0');
	if(b[i] != '\0')
		return -1;
	return 0;

}

inline int find(int e,char *str,int m)
{
	int i,j,k;
	for(i = 0;i < m;i++)
	{
		j = 1;
		if(pri[e+i] != -1)
			j = sc(ent[pri[e + i]].str,str);
		if(j == 0)
			return e + i;
		if(j == 1)
		{
			for(k = m - 1;k > i;k--)
				memcpy(&pri[e+k],&pri[e+k-1],sizeof(int));
			if(m == 20)
				pri[e+i] = pnow++;
			else
				pri[e+i] = snow++;
			strcpy(ent[pri[e+i]].str,str);
			clr(ent[pri[e+i]].page);
			return e + i;
		}

	}
	return -1;
}
inline void ik(int e,int p)
{
	int i,k;
	for(i = 0;i < 9 && ent[pri[e]].page[i] != -1;i++)
	{
		if(ent[pri[e]].page[i] == p)
			return;
		if(ent[pri[e]].page[i] > p)
		{
			for(k = 9;k > i;k--)
				ent[pri[e]].page[k] = ent[pri[e]].page[k-1];
			ent[pri[e]].page[i] = p;
			return;

		}
	}
	ent[pri[e]].page[i] = p;
}

inline void insert(char* str,int page,int n)
{
	int i,j,p;
	for(i = 0;i < n;i++)
		if(str[i] == '%')
		{
			str = str + i + 1;
			n -= (i + 1);
		}
	for(i = 0;i < n;i++)
		if(str[i] != ' ')
			break;
	while(str[n - 1] == ' ')
		n--;
	str[n] = '\0';
	for(j = i;j < n;j++)
		if(str[j] == '$')
		{
			while(str[j - 1] == ' ')
				j--;
			str[j] = '\0';
			p = find(0,str + i,20);
			j++;
			while(str[j] == ' ' || str[j] == '$')
				j++;
			p = find(pri[p] * 5 + 20,str + j,5);
			ik(p,page);
			return;
		}
	p = find(0,str + i,20);
	ik(p,page);
	return;
}

int main()
{
	char t,str[100];
	char *d = (char*) malloc (100000);
	int page = 1,doc = 0,acc,i,j,k,l,len = 0,lt = 0,gc = 0;
	while(1)
	{
		clr(pri);
		len = 0;
		pnow = 0;
		snow = 20;
		do
		{
			gets(d + len);
			lt = strlen(d + len);
			len += lt;
			d[len] = ' ';
			len++;
		}while(d[len - 2] != '*');
		gc = 1;
		t = d[0];
		while(1)
		{
			switch(t)
			{	
				case '*':
					t = d[gc++];
					if(t == '*')
						return 0;
					else
						goto end;
				case '{':
					acc = 0;
					while((t = d[gc++]) != '}')
						str[acc++] = t;
					str[acc] = '\0';
					insert(str,page,acc);
					break;
				case '&':
					page++;
					break;
			}
			t = d[gc++];;
		}
end:		printf("DOCUMENT %d\n",++doc);
		for(i = 0;i < 20 && pri[i] != -1;i++)
		{
			l = pri[i];
			printf("%s",ent[l].str);
			for(k = 0;k < 10 && ent[l].page[k] != -1;k++)
				printf(", %d",ent[l].page[k]);
			putchar(10);
			for(j = l * 5 + 20;j < l * 5 + 30 && pri[j] != -1;j++)
			{
				printf("+ %s",ent[pri[j]].str);
				for(k = 0;k < 10 && ent[pri[j]].page[k] != -1;k++)
					printf(", %d",ent[pri[j]].page[k]);
				putchar(10);
			}
		}
		page = 1;
	}
}
