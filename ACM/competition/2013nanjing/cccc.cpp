#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <list>
#include <map>
using namespace std;
/*
struct edge{
	int to,value,count;
};
*/
short father[10010];
int cc[10010];
int n;
//list<edge> eli[10000];
/*
//map<pair<short,short>,int> gtab;
int getC(int to,int from){
//	map<pair<short,short>,int>::iterator git,gend = gtab.end();
	list<edge>::iterator it,en;
	int count = 1;
//	if((git = gtab.find(make_pair<short,short>(from,to))) != gend)
//		return git->second;
	for(it = eli[to].begin(),en = eli[to].end();it != en;it++)
		if(it->to != from)
			count += getC(it->to,to);
//	gtab[make_pair<short,short>(from,to)] = count;
//	gtab[make_pair<short,short>(to,from)] = n - count;
	
	return count;
}
*/
short getf(short i){
	return father[i] == -1?i:father[i] = getf(i);
}
struct e{
	short f,t;
	int v;
	bool operator<(const e& t) const{
		return v < t.v;
	}
};
int main(){
	int m,i,j,k,l,p,pp,qq;
	map<int,int,less<int> > ans;
	map<int,int>::iterator mit,men;
//	edge ttt;
//	list<edge>::iterator it,en;
	e *etab = new e[500000];
//	ttt.count = 0;
	
	while(scanf("%d%d",&n,&m) != EOF){
		memset(father,0xff,n*sizeof(short));
		for(i = 0;i < n;i++)
			cc[i] = 1;
		ans.clear();
		ans[1<<30] = 0;
//		gtab.clear();
//		for(i = 0;i < n;i++)
//			eli[i].clear();
		for(i = 0;i < m;i++)
			scanf("%hd%hd%d",&etab[i].f,&etab[i].t,&etab[i].v);
		sort(etab,etab+m,less<e>());
		//MST
		for(i = 0,j = 1;j < n;i++){
			k = etab[i].f;
			l = etab[i].t;
			if((pp=getf(k)) != (qq=getf(l))){
				j++;
				ans[etab[i].v] = cc[pp] * cc[qq];
				cc[pp] += cc[qq];
				father[qq] = pp;
//				ttt.value = etab[i].v;
//				ttt.to = k;
//				eli[l].push_back(ttt);
//				ttt.to = l;
//				eli[k].push_back(ttt);
//				ans[ttt.value] = 2 * getC(k,l) * getC(l,k);
			}
		}
//		for(i = 0;i < n;i++)
//			for(it = eli[i].begin(),en = eli[i].end();it != en;it++)
//				if(i < it->to){
//					j = getC(it->to,i);
//					ans[it->value] += 2 * n * j;
//				}
		l = 0;
		mit = ans.end();men = ans.begin();
		do{
			mit--;
			l += mit->second;
			mit->second = l;
		}while(mit != men);

		scanf("%d",&p);
		for(i = 0;i < p;i++){
			scanf("%d",&j);
			printf("%d\n",2 * ans.lower_bound(j)->second);
		}
	}
	delete[] etab;
	return 0;
}

