#include<iostream>
using namespace std;

int sub1(int n);
int sub2(int n);

int main()
{
	int T,n;
	cin >> T;
	while(T--)
	{
		cin >> n;
		cout << sub1(n) << endl;
	}
	return 0;
}

int sub1(int n)
{
	long long end = 0,num = 9,d = 1,sum = 0;
	sum = (end + d + end + num * d) * num / 2;
	while(n > sum)
	{
		end += num * d;
		num *= 10;
		d++;
		sum += (end + d + end + num * d) * num / 2;
	}
	sum -= (end + d + end + num * d) * num / 2;
	while(n > sum)
		sum += (end += d);
	return sub2(n - sum + end);
}

int sub2(int n)
{
	n--;
	int i,num,m;
	for(i = 1,num = 9,m = 0;n >= i * num;i++,m += num,num *= 10)
		n -= i * num;
	m += n / i + 1;
	i = i - n % i - 1;
	while(i--)
		m /= 10;
	return m % 10;
}
