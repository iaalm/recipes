#include<stdio.h>
#include<string.h>
#include <math.h>

char tab[110][110];
int list[30][2],n;
int search(int m,int mini){
	int i,j,k,l = m,i0,i1,j0,j1;
	for(i = mini;i < n;i++){
		for(j = i + 1;j < n;j++){
			i0 = list[i][0];
			i1 = list[i][1];
			j0 = list[j][0];
			j1 = list[j][1];
			if(i0 != j0 && abs(i1 - j1) == abs(i0 - j0) && tab[i0][j1] && tab[j0][i1] && tab[j0][j1] && tab[i0][i1]){
				tab[i0][i1]--;
				tab[i0][j1]--;
				tab[j0][i1]--;
				tab[j0][j1]--;
				k = search(m + 1,i+1);
				if(k == n / 4)
					return k;
				tab[i0][i1]++;
				tab[i0][j1]++;
				tab[j0][i1]++;
				tab[j0][j1]++;
				if(k > l)
					l = k;
			}
		}
	}
	return l;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	while(n != -1){
		memset(tab,0,110*110 * sizeof(char));
		for(i = 0;i < n;i++){
			scanf("%d%d",&j,&k);
			tab[j][k]++;
			list[i][0] = j;
			list[i][1] = k;
		}
		printf("%d\n",search(0,0) * 4);
		scanf("%d",&n);
	}
}
