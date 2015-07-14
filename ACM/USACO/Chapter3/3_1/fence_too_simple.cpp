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
using namespace std;
int countt[501];

int find_n(list<int>& l){
	int i;
	i = l.front();
	if(countt[i] == 1 && l.size() != 1)
		return *(l.begin()++);
	return i;
}

int main(int argc, const char *argv[])
{
	list<int> li[501];
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
	for (i = 0; i < n; i++)
		li[i].sort();

	for(j = 0;j < 501;j++)
		if(countt[j] && countt[j] % 2)
			break;
	if(j == 501)
		for(j = 0;!countt[j];j++);

	fp = fopen("fence.out","w");
	fprintf(fp,"%d\n",j + 1);
	while(countt[j]){
		i = find_n(li[j]);
		fprintf(fp,"%d\n",i + 1);
		countt[i]--;
		countt[j]--;
		li[j].erase(find(li[j].begin(),li[j].end(),i));
		li[i].erase(find(li[i].begin(),li[i].end(),j));
		j = i;
	}
	fclose(fp);

	return 0;
}
