#include <stdio.h>
#include <list>

using namespace std;

struct node{
	int i,j;
};

int main(){
	int n,i,num,m,T,count,I;
	list<node> li;
	list<node>::iterator it,en,ttt;
	node no;
	scanf("%d",&T);
	for(I = 1;I <= T;I++){
		scanf("%d%d",&n,&m);
		li.clear();
		count = 0;
		for(i = 0;i < n;i++){
			scanf("%d",&num);
			for(it = li.begin(),en = li.end();it != en;){
				if((it->i = (it->i | num)) >= m){
					count += (it->j * (it->j + 1) / 2);
					ttt = it;
					it++;
					li.erase(ttt);
				}
				else{
					it->j++;
					it++;
				}
			}
			if(num < m){
				no.i = num;
				no.j = 1;
				li.push_back(no);
			}
		}
		for(it = li.begin(),en = li.end();it != en;it++){
			count += (it->j * (it->j + 1) / 2);
		}
		printf("Case #%d: %d\n",I,count);
	}
	return 0;
}
