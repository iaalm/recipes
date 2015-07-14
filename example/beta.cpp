#include <stdio.h>
#include "smath.h"

int main (int argc, char const* argv[])
{
//	printf("%d,%lf\n",abs(-2),abs(3.0));
//	printf("%lf\n",sqrt(1));
//	printf("%lld\n",fac(4));
//	printf("%lf\n",sin(5));
//	printf("%lf\n",cos(3.1415926));
//	printf("%lf\n",tan(3.1415926));
//	printf("%lf\n",exp(1));
//	printf("%lf\n",ln(1));
	for(int i = 0;i <10000000;i ++)
		pow(2,20.0);
	printf("finish!\n");
	//printf("%lf\n",pow(2,2.5));
//	int a[]={1,3};
//	printf("%lf\n",average(a,2));
//	printf("%lf\n",variance(a,2));
	return 0;
}
