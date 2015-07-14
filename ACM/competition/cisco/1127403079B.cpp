#include<iostream>
#include<string.h>
#include<bitset>

using namespace std;

int main()
{
	int t,i,j,sp,rp;
	bitset<256> set;
	char str[120],result[120];

	cin >> t;
	while(t != 0)
	{
		cin >> str;
		for(i = 0;i < 256;i++)
			set[i] = 0;
		for(sp = 0,rp = 0;sp < strlen(str);sp++)
		{
			if(set[str[sp]] == 0)
			{
				result[rp++] = str[sp];
				set[str[sp]] = 1;
			}
		}
		result[rp] = '\0';
		cout << result <<endl;
		t--;
	}
}