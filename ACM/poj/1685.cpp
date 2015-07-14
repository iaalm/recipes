#include<iostream>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#define abs(X) ((X)>= 0?(X):-(X))
//#include<fstream>
using namespace std;

int h[3][100],n[3],mi[3][100][3][100];
int dp(int fb,int fn,int eb,int en)
{
	int i,j,&mm = mi[fb][fn][eb][en];
	
	if(mi[fb][fn][eb][en])
		return mi[fb][fn][eb][en];

	if(en == 0 && fn == n[fb] - 1 && eb == (fb + 1) % 3)
	{
		return 0;
	}
	mm = (1 << 20);
	if(en != 0)
	{
		if((j = abs(h[fb][fn] -h[eb][en -1]) + dp(fb,fn,eb,en - 1)) < mm)
			mm = j;
	}
	if(fn != n[fb] - 1)
	{
		if((j = abs(h[fb][fn + 1] -h[eb][en]) + dp(fb,fn + 1,eb,en)) < mm)
			mm = j;
	}
	if(en != 0 && fn != n[fb] - 1)
	{
		if((j = abs(h[fb][fn + 1] -h[eb][en - 1]) + dp(fb,fn + 1,eb,en - 1)) < mm)
			mm = j;
	}
	if(eb == (fb + 2) % 3)
		for(i = 0;i < n[(fb + 1) % 3];i++)
		{
			if((j = min(abs(h[fb][fn]- h[(fb + 1) % 3][i]) , abs(h[(fb + 1) % 3][i] - h[eb][en])) + dp(fb,fn,(fb + 1) % 3,i) + dp((fb + 1) % 3,i,eb,en)) < mm)
				mm= j;
			if(en != 0)
			{
				if((j = abs(h[(fb + 1) % 3][i] - h[eb][en -1]) + dp(fb,fn,(fb + 1) % 3,i) + dp((fb + 1) % 3,i,eb,en - 1)) < mm)
					mm= j;
			}
			if(fn != n[fb] - 1)
			{
				if((j = abs(h[fb][fn + 1]- h[(fb + 1) % 3][i]) + dp(fb,fn + 1,(fb + 1) % 3,i) + dp((fb + 1) % 3,i,eb,en)) < mm)
					mm= j;
			}
		}
	return mm;
}
int main()
{
	int T,minc,i,j;
	cin >> T;
	while(T--)
	{
		minc = (1 << 20);
		cin >> n[0] >> n[1] >> n[2];
		for(j = 0;j < 3;j++)
			for(i = 0;i < n[j];i++)
				cin >> h[j][i];
		clr(mi);
		for(i = 0;i < n[1];i++)
			if((j = abs(h[0][n[0] / 2] - h[1][i]) + dp(0,n[0] / 2,1,i) + dp(1,i,0,n[0] / 2)) < minc)
				minc = j;
		for(i = 0;i < n[2];i++)
			if((j = abs(h[0][n[0] / 2] - h[2][i]) + dp(0,n[0] / 2,2,i) + dp(2,i,0,n[0] / 2)) < minc)
				minc = j;
		cout << minc << endl;
	}
	return 0;
}
