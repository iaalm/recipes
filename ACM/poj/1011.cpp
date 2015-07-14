#include<iostream>
#include<cstring>
#include<bitset>
#include<algorithm>
using namespace std;

int N,T,sum,A[70];
bitset<70> used;

bool DFS(int t,int n,int from);

int main()
{
	int i,max;
	while(1)
	{
		cin >> N;
		sum = 0;
		if(N == 0)
			break;
		for(i = 0;i < N;i++)
		{
			cin >> A[i];
			sum += A[i];
		}
		sort(A,A + N,greater<int>());
		max = A[0];
		for(T = max;T < sum;T++)
			if(sum % T == 0)
			{
				used.reset();
				if(DFS(T,sum /  T,0))
					break;
			}
		cout << T <<endl;
	}
	return 0;
}

bool DFS(int t,int n,int from)
{
	if(t == 0)
	{
		if(n == 2)
			return true;
		return DFS(T,n - 1,sum / T - n + 1);
	}
	if(from >= N)
		return false;
	if(t == T)
	{
		while(used[from])
			from++;
		used[from] = 1;
		if(DFS(t - A[from],n,from + 1))
			return true;
		else
		{
			used[from] = 0;
			return false;
		}
	}
	if(used[from] == 0)
	{
		if(A[from] <= t)
		{
			used[from] = 1;
			if(DFS(t - A[from],n,from + 1))
				return true;
			used[from] = 0;
		}
		while(from < N && A[from] == A[from + 1])
		{
			from++;
		}

	}
	return DFS(t,n,from + 1);
}
