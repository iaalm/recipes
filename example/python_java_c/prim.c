#include<stdio.h>
#include<math.h>

int main(){
	unsigned int i,j,k = 0,l;
	for(i = 2;i < (1 << 16);i++){
		l = sqrt(i);
		for(j = 2;j <= l;j++)
			if(i % j == 0){
				k++;
				break;
			}
	}
	printf("%d\n",k);
	return 0;
}
