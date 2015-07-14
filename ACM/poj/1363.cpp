#include<iostream>
using namespace std;

int main()
{
	int max,now,want[1100],fin,i,t,st[1100],head;
	for(t = 0;;t++)
	{
		cin >> max;
		if(max == 0)
			break;
		if(t)
			cout << endl;
		while(1)
		{
			head = 0;
			cin >> i;
			if(i == 0)
				break;
			want[0] = i;
			for(now = 1;now < max;now++)
				cin >> want[now];
			now = 1;
			for(fin = 0;;fin++)
			{
				if(fin == max)
				{
					cout << "Yes" <<endl;
					break;
				}
				if(head && want[fin] == st[head - 1])
				{
					head--;
					continue;
				}
				if(want[fin] == now)
				{
					now ++;
					continue;
				}
				if(want[fin] > now && want[fin] <= max)
				{
					while(now != want[fin])
					{
						st[head++] = now;
						now ++;
					}
					now ++;
					continue;
				}
				cout <<  "No" <<endl;
				break;
			}
		}
	}
	return 0;
}
