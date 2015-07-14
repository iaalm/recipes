#include<iostream>
using namespace std;

int N,Stamp[300],R[60],FLAG,RES[6];
int W(int k,int n,int b,int f,int t);

int main()
{
	int t,i,j,k,p;
	while(cin >> t)
	{
		N = 0;
		do
		{
			Stamp[N++] = t;
			cin >> t;
		}while(t);

		//sort
		for(i = 0;i < N;i++)
		{
			k = i;
			for(j = i + 1;j <  N;j++)
				if(Stamp[j] > Stamp[k])
					k = j;
			if(i != k)
			{
				j = Stamp[i];
				Stamp[i] = Stamp[k];
				Stamp[k] = j;
			}
		}

		cin >> t;
		do
		{
			FLAG = 0;
			k = 1;
			for(i = 4;i > 0 && k;i--)
				for(j = i;j <= 4 && k;j++)
					if((p = W(i,j,0,0,t)) || FLAG)
					{
						k = 0;
						i++;
						j--;
					}
					
			if(i == 0)
				cout <<t << " ---- none" << endl;
			else
			{
				cout <<t << " (" << i << "):";
				if(p == 1)
					cout << " tie" << endl;
				else
				{
					for(p = j - 1;p >= 0;p--)
						cout << " "<<RES[p];
					cout << endl;
				}
			}
			cin >> t;
		}while(t);
	}
	return 0;
}

int W(int k,int n,int b,int f,int t)
{
	int i;
	if(k == 0 && n == 0 && t == 0)
	{
		if(FLAG == 0)
		{
			FLAG = R[0];
			for(i = 0;i < 4;i++)
				RES[i] = R[i];
			return 0;
		}
		if(FLAG == R[0])
		return 1;
	}
	if(k > n || t <= 0 || k < 0 || n < 0)
		return 0;
	for(i = b;i < N;i++)
	{
		if(t < Stamp[i])
			continue;
		R[f] = Stamp[i];
		if(W(k - 1,n - 1,i + 1,f + 1,t-R[f]))
			return 1;
	}
	if(n > k && f > 0)
	{
		R[f] = R[f - 1];
		if(W(k,n - 1,b,f + 1,t-R[f]))
			return 1;
	}
	return 0;
}
