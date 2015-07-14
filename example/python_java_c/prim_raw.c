#include<stdio.h>
#include<math.h>

int main(){
	unsigned int i,j,k = 0;
	for(i = 2;i < (1 << 16);i++)
		for(j = 2;j <= sqrt(i);j++)
			if(i % j == 0){
				k++;
				break;
			}
	printf("%d\n",k);
	return 0;
}
