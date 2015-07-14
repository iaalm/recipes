#include <stdio.h>

int main(){
	int T,m,n,i;
	__int128_t a;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&m,&n);
		a = 1;
		for(i = 1;i < n;i++)
			a *= m;
		printf("%jd\n",a);
	}
	return 0;
}
