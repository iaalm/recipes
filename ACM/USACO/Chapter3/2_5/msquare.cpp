/*
ID: simonin1
LANG: C++
TASK: msquare
*/

#include <stdio.h>
#include <map>
#include <queue>
#include <stack>
using namespace std;

struct infor{
	unsigned int way:2;
	int pre:30;
};
int A(int i){
	int t = 0,j;
	while(i){
		j = i % 10;
		i /= 10;
		t *= 10;
		t += j;
	}
	return t;
}
int B(int i){
	int t,p,q;
	t = i / 10000;
	p = t % 10;
	t /= 10;
	q = (t + p * 1000) * 10000;

	t = i % 10000;
	p = t / 1000;
	t -= p * 1000;
	t *= 10;
	q += t + p;
	return q;
}
int C(int i){
	int t[4];
	t[0] = (i / 10)		% 10;
	t[1] = (i / 100)	% 10;
	t[2] = (i / 100000)	% 10;
	t[3] = (i / 1000000)	% 10;
	i -= t[0] * 10;
	i -= t[1] * 100;
	i -= t[2] * 100000;
	i -= t[3] * 1000000;
	i += t[1] * 10;
	i += t[2] * 100;
	i += t[3] * 100000;
	i += t[0] * 1000000;
	return i;
}
int (*way[3])(int) = {A,B,C};

int main(){
	int i,j,k,l = 0,t;
	map<int,infor> mm;
	queue<int> que;
	stack<char> sta;
	infor ttt;
	FILE *fp = fopen("msquare.in","r");
	for(i = 0;i < 8;i++){
		fscanf(fp,"%d",&t);
		l *= 10;
		l += t;
	}
	fclose(fp);
	if(l == 12345678){
		fp = fopen("msquare.out","w");
		fprintf(fp,"0\n\n");
		fclose(fp);
		return 0;
	}
	que.push(12345678);
	while(1){
		k = que.front();
		que.pop();
		for(i = 0;i < 3;i++){
			j = way[i](k);
			if(j == l)
				goto end; 

			if(mm.find(j) == mm.end()){
				que.push(j);
				ttt.way = i;
				ttt.pre = k;
				mm[j] = ttt;
			}
		}
	}
end:
	sta.push(i + 'A');
	i = 1;
	do{
		i++;
		ttt = mm[k];
		k = ttt.pre;
		sta.push(ttt.way + 'A');
	}while(k != 12345678);
	fp = fopen("msquare.out","w");
	fprintf(fp,"%d\n",i);
	while(!sta.empty()){
		fprintf(fp,"%c",sta.top());
		sta.pop();
	}
	fprintf(fp,"\n");
	fclose(fp);
	return 0;
}
