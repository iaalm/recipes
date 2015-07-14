#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#include<string>
#include<iomanip>
#include<vector>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<bitset>
#include<map>
#include<utility>
#define INF (1<<26)
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;

int main()
{
	int i,j;
	for(i = 1;i < 500;i+=2)
		printf("%d %d\n",i,499 - i);
	for(i = 0;i < 500;i+=2)
		printf("%d %d\n",i,499 - i);
	return 0;
}
