#include<iostream>
using namespace std;
int h,w;
char map[100][100];
const char setx[8] = { 0, 0,-1,-1,-1, 1, 1, 1},
      	   sety[8] = { 1,-1,-1, 0, 1,-1, 0, 1};
int work(int x,int y);

int main()
{
	int i,j,res = 0;
	cin >> h >> w;
	for(i = 0;i <h;i++)
		for(j = 0;j <w;j++)
			cin >> map[i][j];
	for(i = 0;i <h;i++)
		for(j = 0;j <w;j++)
			res += work(i,j);
	cout << res << endl;
	return 0;

}

int work(int x,int y)
{
	int i;
	if(x == -1 || x == h || y == -1 || y == w || map[x][y] != 'W')
		return 0;
	map[x][y] = '.';
	for(i = 0;i < 8;i++)
		work(x + setx[i],y + sety[i]);
	return 1;
}
