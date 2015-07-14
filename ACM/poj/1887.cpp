#include<iostream>
#define FOR(X,F,E) for(X = (F);X<(E);X++)
using namespace std;
int main()
{
	int n,mis[32768][2],i,j,max,acc = 0;
	while(1)
	{
		acc++;
		n = 0;
		max = 1;
		while(1)
		{
			cin >> mis[n][0];
			mis[n][1] = 1;
			if(mis[n][0] == -1)
				break;
			n++;
		}
		if(n == 0)
			return 0;
		FOR(i,0,n)
			FOR(j,i + 1,n)
				if(mis[j][0] <= mis[i][0] && mis[j][1] <= mis[i][1])
				{
					mis[j][1] = mis[i][1] + 1;
					if(mis[j][1] > max)
						max = mis[j][1];
				}
		cout << "Test #" << acc << ":" << endl << "  maximum possible interceptions: " <<  max << endl << endl;
	}
	return 0;
}
