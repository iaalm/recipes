#include<iostream>
#include<stdio.h>
#include<bitset>
#define Z(V) cout << #V << ":"<< (V) << endl
//#include<fstream>
using namespace std;
struct node
{
	int t,len;
	node *p;
} *li[50010] = {NULL};
bitset<50010> bs;
int W(int from,int end,int& re)
{
	node *p;
	int ll = 0,fe,rrr,cc = 0,tt;
	re = 0;
	for(p = li[end];p != NULL;p = p -> p)
		if(p -> t != from)
		{
			tt = W(end,p -> t,rrr);
			ll += tt;
			if(tt)
				cc++;
			if(rrr > re)
				re = rrr;
		}
		else
			fe = p -> len;
	if(ll || bs[end])
		ll += 2 * fe;
	if(bs[end] && cc > 1)
		re = fe;
	else
		if(ll)
			re += fe;
		else
			re = 0;
	return ll;
}

int main()
{
	int n,start,i,j,k,l;
	bs.reset();
	node *p,*q;
	scanf("%d %d",&n,&start);
	//cin >> n >> start;
	for(i = 1;i < n;i++)
	{
		scanf("%d %d %d",&j,&k,&l);
		//cin >> j >> k >> l;
		p = new node;
		p -> p = li[j];
		li[j] = p;
		p -> t = k;
		p -> len = l;
		p = new node;
		p -> p = li[k];
		li[k] = p;
		p -> t = j;
		p -> len = l;
	}
	scanf("%d",&l);
	//cin >> l;
	while(l--)
	{
		scanf("%d",&i);
		//cin >> i;
		bs[i] = 1;
	}
	l = 0;
	k = 0;
	for(p = li[start];p != NULL;p = p -> p)
	{
		l += W(start,p -> t,i);
		if(i > k)
			k = i;
	}
	printf("%d\n",l - k);
	//cout << l - k << endl;
	for(i = 0;i < 50010;i++)
	{
		p = li[i];
		while(p != NULL)
		{
			q = p -> p;
			delete p;
			p = q;
		}
	}
	return 0;
}
