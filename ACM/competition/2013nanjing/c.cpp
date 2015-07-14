#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <list>
#include <map>
using namespace std;
short father[10010];
int cc[10010];
int n;
short getf(short i){
	return father[i] == -1?i:father[i] = getf(father[i]);
}
struct e{
	short f,t;
	int v;
	bool operator<(const e& t) const{
		return v < t.v;
	}
};
map<int,int,less<int> > ans;
e etab[500000];
int main(){
	int m,i,j,k,l,p,rt_a,rt_b;
	map<int,int>::iterator it,men;
	
	while(scanf("%d%d",&n,&m) != EOF){
		memset(father,0xff,10010*sizeof(short));
		for(i = 0;i < n;i++)
			cc[i] = 1;
		ans.clear();
		ans[1<<30] = 0;
		for(i = 0;i < m;i++)
			scanf("%hd%hd%d",&etab[i].f,&etab[i].t,&etab[i].v);
		sort(etab,etab+m,less<e>());
		
		for(i = 0,j = 1;j < n;i++){
			k = etab[i].f;
			l = etab[i].t;
			rt_a = getf(k);
			rt_b = getf(l);
			if(rt_a != rt_b){
				j++;
				ans[etab[i].v] = cc[rt_a] * cc[rt_b];
				cc[rt_a] += cc[rt_b];
				father[rt_b] = rt_a;
			}
		}
		l = 0;
		it = ans.end();men = ans.begin();
		do{
			it--;
			l += it->second;
			it->second = l;
		}while(it != men);
		scanf("%d",&p);
		for(i = 0;i < p;i++){
			scanf("%d",&j);
			printf("%d\n",2 * ans.lower_bound(j)->second);
		}
	}
	return 0;
}

