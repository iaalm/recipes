/*
ID: simonin1
LANG: C++
TASK: shopping
*/

#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>

using namespace std;
struct so{
	int dz[5];
	int p;
};

int gen(int* tab){
	int i,j,t = 0;
	for(i = 4,j = 1;i>= 0;i--,j*= 6)
		t += tab[i] * j;
	return t;
}

int main(){
	int tab[6*6*6*6*6],i,j,k,map[1000],n=0;
	queue<so> qu;
	vector<so> li;
	FILE *fp = fopen("shopping.in","r");
	so t,target;
	bzero(&target,sizeof(t));
	memset(&tab,0x0f,6*6*6*6*6*sizeof(int));
	tab[0] = 0;
	fscanf(fp,"%d",&k);
	while(k--){
		fscanf(fp,"%d",&j);
		while(j--){
			fscanf(fp,"%d",&i);
			fscanf(fp,"%d",&i);
		}
		fscanf(fp,"%d",&t.p);
	}
	memset(map,0xff,1000*sizeof(int));
	fscanf(fp,"%d",&k);
	j = 0;
	while(k--){
		fscanf(fp,"%d",&i);
		if(map[i] == -1)
			map[i] = j++;
		fscanf(fp,"%d",&target.dz[map[i]]);
		bzero(&t,sizeof(t));
		t.dz[map[i]] = 1;
		fscanf(fp,"%d",&t.p);
		li.push_back(t);
		n++;
	}

	rewind(fp);
	fscanf(fp,"%d",&k);
	while(k--){
		fscanf(fp,"%d",&j);
		bzero(&t,sizeof(t));
		while(j--){
			fscanf(fp,"%d",&i);
			fscanf(fp,"%d",&t.dz[map[i]]);
		}
		fscanf(fp,"%d",&t.p);
		li.push_back(t);
		n++;
	}
	fclose(fp);
	bzero(&t,sizeof(t));
	qu.push(t);
	while(!qu.empty()){
		t = qu.front();
		for(i = t.p;i < n;i++){
			t = qu.front();
			k = 1;
			for(j = 0;j < 5;j++){
				t.dz[j] += li[i].dz[j];
				if(t.dz[j] > target.dz[j])
					k = 0;
			}
			if(k){
				j = gen(t.dz);
				k = gen(qu.front().dz);
				if(tab[j] > tab[k] + li[i].p){
					tab[j] = tab[k] + li[i].p;
					t.p = i;
					qu.push(t);
				}
			}
		}
		qu.pop();

	}
	fp = fopen("shopping.out","w");
	fprintf(fp,"%d\n",tab[gen(target.dz)]);
	fclose(fp);

	return 0;
}

