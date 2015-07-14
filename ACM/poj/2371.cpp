#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
using namespace std;

int main()
{
	int hash[5000],n,acc,sum,i;
	char t;
	cin >> acc;
	clr(hash);
	while(acc--)
	{
		cin >> n;
		n--;
		hash[n]++;
	}
	cin >> t >> t >> t;
	cin >> acc;
	while(acc--)
	{
		cin >> n;
		sum = 0;
		for(i = 0;n > sum;i++)
			sum += hash[i];
		cout << i << endl;
	}
	return 0;
}
