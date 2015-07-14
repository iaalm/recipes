/*
ID: simonin1
LANG: C++
TASK:humble
*/

#include<fstream>

using namespace std;

struct node
{
	unsigned long num;
	unsigned int max;
	node *p;
};

int main()
{
	ifstream in("humble.in");
	ofstream out("humble.out");
	int gk,gn,i,j,now = 0,*gp;
	node *head,*p,*q;
	in >> gk >> gn;
	gp = new int[gk];
	for(i = 0;i < gk;i++)
	        in >> gp[i];
	head = new node;
	head -> num = 1;
	head -> max = 0;
	head -> p = NULL;
	
	for(;now != gn;now++)
	{
		for(i = head -> max;i < gk;i++)
		{
			p = new node;
			p -> num = j = head -> num * gp[i];
			p -> max = i;
			for(q = head;;q = q -> p)
				if(q -> p == NULL ||q -> p -> num > j)
					break;
			p -> p = q -> p;
			q -> p = p;
		}
		q = head;
		head = head -> p;
		delete q;
	}
	out << head -> num << endl;

	do
	{
		p = head;
		head = head -> p;
		delete p;
	}while(head != NULL);
	delete[] gp;
	return 0;
}
