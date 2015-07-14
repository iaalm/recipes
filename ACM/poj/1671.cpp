#include<iostream>
#include<iomanip>
#define TRAN(X,Y) ((X)*((X)-1)/2+(Y)- 1)
#define MAX_TABLE 5000
using namespace std;

double table[MAX_TABLE];
double W(int n,int p)
{
	if(n < p || p == 0)
		return 0;
	if(n == 1)
		return 1;
	if(table[TRAN(n,p)])
		return table[TRAN(n,p)];
	table[TRAN(n,p)] = W(n - 1,p) * p + W(n - 1,p - 1);
	return W(n - 1,p) * p + W(n - 1,p - 1);
}

int main()
{
	int n,i;
	double result;
	for(i = 0;i < MAX_TABLE;i++)
		table[i] = 0;
	while(1)
	{
		cin >> n;
		if(n == 0)
			return 0;
		result = 0;
		for(i = 1;i <= n;i++)
			result += W(n,i);
		cout << n << " " << fixed << setprecision(0) << result << endl;
	}
}
