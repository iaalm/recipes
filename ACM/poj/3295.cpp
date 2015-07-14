#include<cstdio>
#include<cstdlib>

unsigned int W(char* &wff)
{
	unsigned p,q;
	switch(*wff++)
	{
		case 'K':
			p = W(wff);
			q = W(wff);
			return (p & q);
		case 'A':
			p = W(wff);
			q = W(wff);
			return (p | q);
		case 'N':
			return ~W(wff);
		case 'C':
			p = W(wff);
			q = W(wff);
			return ~(~p & q);
		case 'E':
			p = W(wff);
			q = W(wff);
			return ~(p ^ q);
		case 'p':
			return 0xffff0000;
		case 'q':
			return 0xff00ff00;
		case 'r':
			return 0xf0f0f0f0;
		case 's':
			return 0xcccccccc;
		case 't':
			return 0xaaaaaaaa;
	}
}

int main()
{
	char wff[127],*t;
	while(1)
	{
		gets(wff);
		t = wff;
		if(wff[0] == '0')
			return 0;
		if(W(t) == 0xffffffff)
			puts("tautology");
		else
			puts("not");
	}
}
