#include <cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

double length(const double& a,const double& b,const double& c,const double& x1,double x2)
{
	double y1=2*a*x1+b;
	double thi1=atan(y1);
	double k1=sin(thi1);
	double l1=0.5*(k1/(1-k1*k1)+log( abs( (1+k1) / sqrt(1-k1*k1) ) ));
	
	double y2=2*a*x2+b;
	double thi2=atan(y2);
	double k2=sin(thi2);
	double l2=0.5*(k2/(1-k2*k2)+log(abs((1+k2)/sqrt(1-k2*k2))));

	return abs(l2-l1)/2/a;
}

int main()
{
	double len=length(1,0,0,-2,-1);
	printf("%lf\n",len*2);
	return 0;
}
