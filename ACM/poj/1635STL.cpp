#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

string W(string s)
{
	vector<string> v;
	unsigned int i,from = 0;
	int acc = 0;;
	for(i = 0;i < s.length();i++)
	{
		if(s[i] == '0')
			acc--;
		else
			acc++;
		if(acc == 0)
		{
			v.push_back(W(s.substr(from + 1,i - from - 1)));
			from = i + 1;
		}
	}
	sort(v.begin(),v.end(),less<string>());
	s.clear();
	for(i = 0;i < v.size();i++)
		s += '0' + v[i] + '1';
	return s;
}

int main()
{
	int T;
	string a,b;
	cin >> T;
	while(T--)
	{
		cin >> a;
		cin >> b;
		if(a.length() != b.length())
		{
			cout << "different" << endl;
			continue;
		}
		a = W(a);
		b = W(b);
		if(a == b)
			cout << "same" << endl;
		else
			cout << "different" << endl;
	}
	return 0;
}
