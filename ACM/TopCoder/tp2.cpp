#include<iostream>
#include<string>
#include<vector>
using namespace std;

class TurnOffLights
{
	int on,br[16];
	public:
		int fewestMoves(vector <string> board);
		int search(int f,int n);
		inline void change(int a)
		{
			if(br[a])
				on--;
			else
				on++;
			br[a] = 1 - br[a];
		}
};

int TurnOffLights::fewestMoves(vector <string> board)
{
	int i,j;
	on = 0;
	for(i =0;i < 4;i++)
		for(j = 0;j < 4;j++)
		{
			br[(i << 2) + j] = board[i][j] - '0';
			if(br[(i << 2) + j] == 1)
				on++;
		}
	return search(0,0);
}
int TurnOffLights::search(int f,int n)
{
	int i;
	if(on == 0)
		return n;
	for(;f < 32;f++)
	{
		if(f > 15)
			i = 2;
		else
			i = 1;
		change(f & 15);
		if(f | 16)
		{
			if(f % 4 != 0)
				change(f - 1);
			if(f % 4 != 3)
				change(f + 1);
			if(f < 12)
				change(f + 4);
			if(f > 3)
				change(f - 4);
		}
		if(search(f,n + i))
			return n + i;
		change(f & 15);
		if(f | 16)
		{
			if(f % 4 != 0)
				change(f - 1);
			if(f % 4 != 3)
				change(f + 1);
			if(f < 12)
				change(f + 4);
			if(f > 3)
				change(f - 4);
		}
	}
	return 0;
}

//---------------------------------------------------------------
int main()
{
	TurnOffLights TT;
	vector<string> ss;
	ss.push_back("0100");
	ss.push_back("1110");
	ss.push_back("0100");
	ss.push_back("0000");
	cout << TT.fewestMoves(ss) << endl;
	return 0;
}
