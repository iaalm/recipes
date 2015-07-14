#include<iostream>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;

int main()
{
	int T,N,*f1,*f0,t,i;
	cin >> T;
	FOR(t,0,T)
	{
		cin >> N;
		f1 = new int[N + 1];
		f0 = new int[N + 1];
		f1[0] = 0;
		f0[0] = 1;
		FOR(i,0,N)
		{
			f0[i+1] = f1[i] + f0[i];
			f1[i+1] = f0[i];
		}
		cout << "Scenario #" << t + 1  << ":" << endl << f1[N] + f0[N] << endl << endl;
		delete[] f1;
		delete[] f0;
	}
	return 0;
}
