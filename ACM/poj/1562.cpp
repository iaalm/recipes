#include<iostream>
#include<fstream>

#define TRAN(X,Y) ((X) * y + (Y))

using namespace std;

char *mar;
int x,y;

int work(int i,int j);

int main()
{
	int i,j,R;
	//ifstream cin("in.txt");//
	while(1)
	{
		R = 0;
		cin >> x >> y;
		if(x == 0)
			break;
		mar = new char[x * y];
		for(i = 0;i < x;i++)
			for(j = 0;j < y;j++)
				cin >> mar[TRAN(i,j)];
		for(i = 0;i < x;i++)
			for(j = 0;j < y;j++)
				R += work(i,j);
		cout << R <<endl;
		delete mar;
	}
	return 0;
}

int work(int i,int j)
{
	int p,q;
	if(i == -1 || i == x || j == -1 || j == y || mar[TRAN(i,j)] == '*')
		return 0;
	mar[TRAN(i,j)] = '*';
	for(p = -1;p <= 1;p++)
		for(q = -1; q <= 1;q++)
			work(i + p,j + q);
	return 1;
}
