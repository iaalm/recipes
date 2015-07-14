#include<iostream>
#define MAX 200005
#define MIN_INT (-10000000)

using namespace std;

int main()
{
	int s[100],f[100],res[MAX],i,j,N;
	cin >> N;
	for(i = 0;i < N;i++)
		cin >> s[i] >> f[i];
	for(i = 0;i < MAX;i++)
		res[i] = MIN_INT;
	for(i = 0;i < N;i++)
	{
		if(s[i] <= 0)
		{
			for(j = 0;j < MAX;j++)
				if(res[j] != MIN_INT && res[s[i] + j] < res[j] + f[i])
					res[s[i] + j] = res[j] + f[i];
		}
		else
		{
			for(j = MAX - 1;j >= 0;j--)
				if(res[j] != MIN_INT && res[s[i] + j] < res[j] + f[i])
					res[s[i] + j] = res[j] + f[i];
		}
		if(res[s[i] + 100000] < f[i])
			res[s[i] + 100000] = f[i];
	}
	j = 0;
	for(i = 100000;i < MAX;i++)
		if(res[i] >= 0 && j < i - 100000 + res[i])
			j = i - 100000 + res[i];
	cout << j << endl;
	return 0;
}
