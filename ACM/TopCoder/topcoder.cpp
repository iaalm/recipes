#include<vector>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;

class AccountBalance
{
	private:
	public:
		int processTransactions(int,vector<string>);
};

int AccountBalance::processTransactions(int start,vector<string> bal)
{
	istringstream ss;
	char d;
	int num;
	for(vector<string>::iterator it = bal.begin();it != bal.end();it++)
	{
		ss.clear();
		ss.str(*it);
		ss >> d >> num;
		if(d == 'C')
			start += num;
		if(d == 'D')
			start -= num;
	}
	return start;
};

//********************************************************

int main()
{
	AccountBalance A;
	vector<string> s;
	s.push_back("C 1000");
	s.push_back("D 500");
	s.push_back("D 350");
	cout << A.processTransactions(100,s) << endl;
	return 0;
}
