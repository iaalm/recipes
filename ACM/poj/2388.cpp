#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int n,i;
	cin >> n;
	int set[n];
	for(i = 0;i < n;i++)
		cin >> set[i];
	sort(set,set + n,less<int>());
	cout << set[n / 2] << endl;
	return 0;
}
