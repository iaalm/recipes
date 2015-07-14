#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#define INT_MAX (1 << 30)
using namespace std;

int main()
{
	int len,n,i,j,k;
	cin >> len >> n;
	char dna[n][len];
	int ss[n];
	clr(ss);
	for(i = 0;i < n;i++)
		for(j = 0;j < len;j++)
		{
			cin >> dna[i][j];
			for(k = j - 1;k >= 0;k--)
				if(dna[i][j] < dna[i][k])
					ss[i]++;
		}
	/*
	for(i = 0;i < n;i++)
	{
		k = i;
		for(j = i + 1;j < n;j++)
			if(ss[j] < ss[k])
				k =j;
		if(i != k)
		{
			for(j = 0;i < len;j++)
				t[j] = dna[i][j];
			for(j = 0;i < len;j++)
				dna[i][j] = dna[k][j];
			for(j = 0;i < len;j++)
				dna[k][j] = t[j];
			j = ss[i];
			ss[i] = ss[k];
			ss[k] = j;
		}
	}
	*/
	for(i = 0;i < n;i++)
	{
		k = 0;
		for(j = 0;j < n;j++)
			if(ss[j] < ss[k])
				k = j;
		for(j = 0;j < len;j++)
			cout << dna[k][j];
		ss[k] = INT_MAX;
		cout << endl;
	}
	return 0;
}
