#include<string.h>
#include<stdlib.h>
int kmp(char* pattern,char* str,int start){
	int i,j;
	int n = strlen(pattern);
	int m = strlen(str);
	int *next = (int*)alloca(sizeof(int)*n);
	next[0] = -1;
	i = 0;j = -1;
	while(i < n){
		if(j == -1 || pattern[i] == pattern[j]){
			i++;
			j++;
			next[i] = j;
		}
		else
			j = next[j];
	}
	i = start;j = 0;
	while(n - j + i <= m){
		if(j == n)
			return i - n;
		if(j == -1 || str[i] == pattern[j]){
			i++;
			j++;
		}
		else
			j = next[j];
			
	}
	return -1;
}
#include<stdio.h>

int main(){
	char str1[100],str2[100];
	while(1){
		gets(str1);
		gets(str2);
		printf("%d\n",kmp(str1,str2,0));
	}
}
