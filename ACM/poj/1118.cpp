#include<iostream>

using namespace std;

struct point
{
	int x,y;
};

int main()
{
	int num,max,now,x,y,i,j,k;
	point *p;
	while(1)
	{
		max = 0;
		cin >> num;
		if(num == 0)
			break;
		p = new point[num];
		for(i = 0;i < num ;i++)
			cin >> p[i].x >> p[i].y;
		if(num < 3)
		{
			cout << num << endl;
			continue;
		}
		for(i = 0;i < num;i++)
			for(j = i + 1;j < num;j++)
			{
				now = 2;
				x = p[i].x - p[j].x;
				y = p[i].y - p[j].y;
				for(k = j + 1; k < num;k++)
				{
					if((p[k].x - p[j].x) * y ==  (p[k].y  - p[j].y) * x)
						now++;
				}
				if(now > max)
					max = now;
			}
		cout << max << endl;
		delete p;
	}
	return 0;
}
