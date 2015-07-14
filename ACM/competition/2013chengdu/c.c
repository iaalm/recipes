#include<stdio.h>
#include <string.h>

int main(){
	char str[150];
	int n,i,l;
	scanf("%d",&n);
	for(i = 1;i <= n;i++){
		scanf("%s",str);
		l = strlen(str);
		if(str[l-4] == 'd' && str[l-3] == 'e' &&str[l-2] == 's' &&str[l-1] == 'u' )
			str[l-4] = '\0';
		printf("Case #%d: %snanodesu\n",i,str);
	}
	return 0;
}

