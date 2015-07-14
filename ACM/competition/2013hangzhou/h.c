#include <stdio.h>
#include <string.h>
int tab[2010],n,martix[1010][2010];
int search(int i,int j,int max){
	if(martix[i][j])
		return martix[i][j];
	int p,q,k,l = 0;
	for(p = i + 1;p < max;p++)
		for(q = j - 1;q >= 0;q--)
			if(tab[p] == tab[q])
				if(l < (k = search(p,q,max)))
					l = k;
	if(l >= n)
		l = n;
	else
		l++;
	martix[i][j] = l;
	return l;
}
int main(){
	int i,j,k,l;
	scanf("%d",&n);
	while(n){
		memset(martix,0x00,1010*2010*sizeof(int));
		l = 0;
		for(i = 0;i < n;i++)
			scanf("%d",tab+i);
		memcpy(tab+n,tab,n*sizeof(int));
		for(i = 0;i < n;i++)
			for(j = 0;j < 2*n;j++)
				if(tab[i] == tab[j])
					if(l < (k = search(i,j,i + n)))
						l = k;
		printf("%d\n",l);
		scanf("%d",&n);
	}
	return 0;
}
