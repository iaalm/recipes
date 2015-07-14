#include<stdio.h>
#include <string.h>
int tab[10][5000];
int pow_2[10]={1,2,4,8,16,32,64,128,256,512};
int pow_10[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int fun(int ca,int b){
	if(b < 0)
		return 0;
	if(ca == 0)
		return 1;
	if(tab[ca][b] != -1)
		return tab[ca][b];
	int n = 0,i;
	for(i = 0;i < 10;i++)
		n += fun(ca - 1,b - i * pow_2[ca-1]);
	tab[ca][b] = n;
	return n;
}
int f(int a){
	int n = 0,l,i;
	for(i = 9;i >= 0;i--){
		l = a / pow_10[i];
		n += l * pow_2[i];
		a -= l * pow_10[i];
	}
	return n;
}
int main(){
	int a,b,i,j,k,l,N,I,count;
	memset(tab,0xff,5000*10*sizeof(int));
	scanf("%d",&N);
	for(I = 1;I <= N;I++){
		scanf("%d%d",&a,&b);
		a = f(a);
		b++;
		count = 0;
		for(i = 9;i >= 0;i--){
			l = b / pow_10[i];
			b -= l * pow_10[i];
			for(j = 0;j < l;j++)
				count += fun(i,a - j * pow_2[i]);
			a -= l * pow_2[i];
		}
		printf("Case #%d: %d\n",I,count);
	}
	return 0;
}
