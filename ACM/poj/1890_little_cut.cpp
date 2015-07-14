#include<stdio.h>
#include<string.h>

inline int min(int a,int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

int error[8],pro[8],tp[5][2],used[8],terr[8],np,nt,tord[8],ord[8];
void DFS(int n,int tpt,int tt)
{
	int i,j,k,l,m[8];
	for(l =0;l < 8;l++)
		m[l] = terr[l];
	if(n == np)
	{
		for(i = 1;i < 8;i++)
		{
			if(error[i] > terr[i])
			{
				for(j = 0;j < 8;j++)
				{
					error[j] = terr[j];
					ord[j] = tord[j];
				}
				break;
			}
			if(error[i] < terr[i])
				break;
		}
		return ;
	}
	for(i = 0;i < np;i++)
		if(!used[i])
		{
			k = tpt;
			used[i] = 1;
			tord[n] = i;
			while((j =  min(tp[k][1] - tt,pro[i] + tt - tp[k][1])) >= 0)
				terr[tp[k++][0]] += j;
			if(error[1] > terr[1] || (error[1] == terr[1] && error[2] >= terr[2]))
				DFS(n + 1,k,tt + pro[i]);
			for(l =0;l < 8;l++)
				terr[l] = m[l];
			used[i] = 0;
		}
}

int main()
{
	int acc = 0,i,j,k;
	while(1)
	{
		scanf("%d",&np);
		if(__builtin_expect(np == 0,0))
			return 0;
		acc++;
		memset(used,0,sizeof(used));
		memset(error,0,sizeof(error));
		memset(terr,0,sizeof(terr));
		error[1] = 100;
		for(i = 0;i < np;i++)
			scanf("%d",pro + i);
		scanf("%d",&nt);
		for(i = 0;i < nt;i++)
			scanf("%d %d",&tp[i][0],&tp[i][1]);
		for(i = 0;i < nt;i++)
		{
			k = i;
			for(j = i + 1;j < nt;j++)
				if(tp[j][1] < tp[k][1])
					k = j;
			if(k != i)
			{
				j = tp[k][0];
				tp[k][0] = tp[i][0];
				tp[i][0] = j;
				j = tp[k][1];
				tp[k][1] = tp[i][1];
				tp[i][1] = j;
			}
		}
		DFS(0,0,0);
		printf("Data set %d\nOrder:",acc);
		for(i = 0,j = 0;i < np;i++)
		{
			printf(" %d",pro[ord[i]]);
			j += error[i];
		}
		printf("\nError: %d\n",j);
	}
}
