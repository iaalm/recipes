/*
ID: simonin1
LANG: C++
TASK: fence
*/

#include <stdio.h>
#include <string.h>
#include <functional>
#include <algorithm>
#include <list>
#include <stack>
using namespace std;
int countt[501];
list<int> li[501];
stack<int> ans;

int find_n(list<int>& l){
	int i;
	i = l.front();
	if(countt[i] == 1 && l.size() != 1)
		return *(l.begin()++);
	return i;
}

void search(int j,FILE* fp){
	int i;
	while(countt[j]){
		i = li[j].front();
		countt[i]--;
		countt[j]--;
		li[j].erase(find(li[j].begin(),li[j].end(),i));
		li[i].erase(find(li[i].begin(),li[i].end(),j));
		search(i,fp);
	}
	ans.push(j+1);
}
int main(int argc, const char *argv[])
{
	bzero(countt,501*sizeof(int));
	int n,i,j,k;
	FILE *fp = fopen("fence.in","r");
	fscanf(fp,"%d",&n);
	for (i = 0; i < n; i++){
		fscanf(fp,"%d %d",&j,&k);
		j--;
		k--;
		li[j].push_back(k);
		li[k].push_back(j);
		countt[j]++;
		countt[k]++;
	}
	for (i = 0; i < 501; i++)
		li[i].sort();

	for(j = 0;j < 501 ;j++)
		if(countt[j] && countt[j] % 2)
			break;
	if(j == 501)
		for(j = 0;!countt[j];j++);

	search(j,fp);
	fp = fopen("fence.out","w");
	while(!ans.empty()){
		fprintf(fp,"%d\n",ans.top());
		ans.pop();
	}
	fclose(fp);

	return 0;
}
