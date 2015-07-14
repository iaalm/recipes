#include <stdio.h>

int main(){
	int i,j;
	scanf("%d%d",&i,&j);
	while(i){
		if((i-1) % (j + 1))
			puts("Jiang");
		else
			puts("Tang");
	scanf("%d%d",&i,&j);
	}
	return 0;
}
