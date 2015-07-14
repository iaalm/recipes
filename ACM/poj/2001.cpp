#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char name[1000][25];
	int num[1000],i,j,k,n = 0;
	memset(num,0,sizeof(num));
	while(cin >> name[n])
		n++;
	for(i = 0;i < n;i++)
		for(j = i + 1;j < n;j++)
		{
			k = 0;
			while(name[i][k] == name[j][k])
				k++;
			if(num[i] <= k)
			{
				if(name[i][k] != '\0')
					num[i] = k + 1;
				else
					num[i] = k;
			}
			if(num[j] <= k)
			{
				if(name[j][k] != '\0')
					num[j] = k + 1;
				else
					num[j] = k;
			}
		}
	for(i = 0;i < n;i++)
	{
		cout << name[i] << " ";
		for(j = 0;j < num[i];j++)
			cout << name[i][j];
		cout << endl;
	}
	return 0;
}
