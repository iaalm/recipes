#include<iostream>
#include<bitset>
using namespace std;

bitset<10000> set;
int N,a[10000],sum;

bool w(int m,int s,int t);
void sort();

int main()
{
	int t,i;
	cin >> t;
	while(t--)
	{
		sum = 0;
		cin >> N;
		for(i = 0;i < N;i++)
		{
			cin >> a[i];
			sum += a[i];
		}
		if(sum % 4 != 0)
		{
			cout << "no" << endl;
			continue;
		}
		sum /= 4;
		sort();
		set.reset();
		set[0] = 1;
		if(w(1,sum - a[0],1))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	return 0;
}

bool w(int m,int s,int t)
{
	if(s == 0)
	{
		if(t == 4)
			return true;
		return w(1,sum,t + 1);
	}
	if(m == N)
		return false;
	if(set[m] == 1)
		return w(m + 1,s,t);
	if(a[m] <= s)
	{
		set[m] = 1;
		if(w(m + 1,s - a[m],t))
			return true;
	}
	set[m] = 0;
	return w(m + 1,s,t);
}

void sort()
{
	int i,j,index;
	for(i = 0;i < N;i++)
	{
		index = i;
		for(j = i + 1;j <  N;j++)
			if(a[j] > a[i])
				index = j;
		if(i != index)
		{
			j = a[i];
			a[i] = a[index];
			a[index] = j;
		}
	}
}
