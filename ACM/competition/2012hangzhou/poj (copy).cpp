#include<cstdio>
#include<cstdlib>
#include<cstring>
#define clr(X) memset(X,0,sizeof(X))
#define INF (1<<26)
#define max(X,Y) ((X)>=(Y)?(X):(Y))
#define min(X,Y) ((X)>=(Y)?(Y):(X))
//#define DEBUG

struct rec
{
	int xs,ys,xe,ye,col;
	rec *p;
};

int main()
{
#ifdef DEBUG
	freopen("in.txt","r",stdin);
#endif
	long long res[8];
	int T,n,k = 0;
	rec *head,*p,*r,t;
	char ct;
	scanf("%d",&T);
	while(T--) {
		clr(res);
		head = new rec;
		head->xs = 0;
		head->ys = 0;
		head->xe = 1000000001;
		head->ye = 1000000001;
		head->col = 0;
		head->p = NULL;

		scanf("%d",&n);
		while(n--) {
			scanf(" %c%d%d%d%d",&ct,&t.xs,&t.ys,&t.xe,&t.ye);
			switch(ct) {
				case'R':t.col = 1;break;
				case'G':t.col = 2;break;
				case'B':t.col = 4;break;
			}
			for(p = head;p != NULL;p = p->p) {
				if((t.col & p->col) || t.xs >= p->xe || t.xe <= p->xs || t.ys >= p->ye || t.ye <= p->ys)
					continue;
				if(p->xs < t.xs) {
					r = new rec;
					memcpy(r,p,sizeof(rec));
					r->p = head;
					head = r;
					r->xe = t.xs;
				}
				if(p->xe > t.xe) {
					r = new rec;
					memcpy(r,p,sizeof(rec));
					r->p = head;
					head = r;
					r->xs = t.xe;
				}
				if(p->ys < t.ys) {
					r = new rec;
					r->p = head;
					head = r;
					r->ye = t.ys;
					r->ys = p->ys;
					r->col = p->col;
					r->xs = max(t.xs,p->xs);
					r->xe = min(t.xe,p->xe);
				}
				if(p->ye > t.ye) {
					r = new rec;
					r->p = head;
					head = r;
					r->ys = t.ye;
					r->ye = p->ye;
					r->col = p->col;
					r->xs = max(t.xs,p->xs);
					r->xe = min(t.xe,p->xe);
				}
				p->xs = max(p->xs,t.xs);
				p->ys = max(p->ys,t.ys);
				p->xe = min(p->xe,t.xe);
				p->ye = min(p->ye,t.ye);
				res[p->col] -= ((p->ye - p->ys) * (long long)(p->xe - p->xs));
				p->col |= t.col;
				res[p->col] += ((p->ye - p->ys) * (long long)(p->xe - p->xs));
			}
		}
		while(head != NULL) {
			p = head -> p;
			delete head;
			head = p;
		}
		printf("Case %d:\n%lld\n%lld\n%lld\n%lld\n%lld\n%lld\n%lld\n",++k,res[1],res[2],res[4],res[3],res[5],res[6],res[7]);
	}
	return 0;
}
#ifdef DEBUG
void P(rec *p) {
	while(p != NULL) {
		printf("%d %d %d %d %d\n",p->xs,p->ys,p->xe,p->ye,p->col);
		p = p->p;
	}
}
#endif
