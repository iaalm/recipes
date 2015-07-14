#include<iostream>
#include<bitset>

using namespace std;

int N,NUM[15];
bitset<15> S;
bool F;

void work(int t,int a);

int main()
{
	int t,i;
	while(1)
	{
		F = false;
		cin >> t >> N;
		if(t == 0)
			break;

		S.reset();
		for(i = 0;i < N;i++)
			cin >> NUM[i];
		cout << "Sums of " << t << ":" << endl;
		work(t,0);
		if(!F)
			cout << "NONE" << endl;
	}
	return 0;
}

void work(int t,int a)
{
	int i;
	if(a == N)
		return;
	if(NUM[a] == NUM[a - 1] && S[a - 1] == 0)
	{
		S[a] = 0;
		work(t,a + 1);
		return;
	}
	if(NUM[a] > t)
	{
		S[a] = 0;
		work(t,a + 1);
		return;
	}
	if(NUM[a] == t)
	{
		for(i = 0;i < a;i++)
			if(S[i] == 1)
				cout << NUM[i] << "+";
		cout << NUM[a] << endl;
		F = true;
		S[a] = 0;
		work(t,a + 1);
		return;
	}
	S[a] = 1;
	work(t - NUM[a],a + 1);
	S[a] = 0;
	work(t,a + 1);
	
}
