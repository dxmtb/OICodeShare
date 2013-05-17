/*
ID: dxmtb
PROG: 线性规划与网络流24题 餐巾计划问题
TIME: 2011.02.04
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=2000;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int p,int q,int r,Node *n,Node *m=NULL):
	     v(p),c(q),w(r),next(n),back(m){}
	void * operator new (unsigned ,void *p){return p;}
}*adj[MAXN];

Node *mem;
inline void addedge(int u,int v,int c,int w)
{
//	printf("add %d %d %d %d\n",u,v,c,w);
	adj[u]=new(mem++) Node(v,c,w,adj[u]);
	adj[v]=new(mem++) Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int dis[MAXN],S,T;
int fo[MAXN];
Node *fp[MAXN];
deque<int> q;
bool spfa()
{
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[S]=0;
	q.push_back(S);
	while(q.size())
	{
		int u=q.front();q.pop_front();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				fo[p->v]=u;
				fp[p->v]=p;
				if (q.empty()||dis[p->v]>dis[q.front()])
					q.push_back(p->v);
				else 
					q.push_front(p->v);
			}
	}
	return dis[T]!=oo;
}	

int mincost;//,maxflow;
void augment()
{
	int delta=oo;
	for(int u=fo[T],v=T;v!=S;v=u,u=fo[u])	
		if (delta>fp[v]->c)
			delta=fp[v]->c;
	for(int u=fo[T],v=T;v!=S;v=u,u=fo[u])
	{
		fp[v]->c-=delta;
		fp[v]->back->c+=delta;
	//	mincost+=fp[v]->w*delta;
	}
//	maxflow+=delta;
	mincost+=delta*dis[T];
}

void solve()
{
	while(spfa())
		augment();
}

int N,p,m,f,n,s;
int main()
{
	freopen("napk.in","r",stdin);
	freopen("napk.out","w",stdout);
	scanf("%d%d%d%d%d%d",&N,&p,&m,&f,&n,&s);
	//int sum=0;
	S=0;T=2*N+1;
	mem=new Node[N*13];
	for(int i=1;i<=N;i++)
	{
		int a;
		scanf("%d",&a);
	//	addedge(i*2-1,i*2,a,-p);
		addedge(S,i*2-1,a,0);
		addedge(i*2,T,a,0);
		addedge(S,i*2,oo,p);
		if (i!=N)
			addedge(i*2-1,i*2+1,oo,0);
		if (i+m<=N)
			addedge(i*2-1,(i+m)*2,oo,f);
		if (i+n<=N)
			addedge(i*2-1,(i+n)*2,oo,s);
	//	sum+=a;
	}
	/*
	addedge(S,1,oo,p);
	for(int i=1;i<N;i++)
		addedge(i*2-1,i*2+1,oo,0);
	for(int i=1;i<=N-m;i++)
		addedge(i*2,(i+m)*2-1,oo,f);
	for(int i=1;i<=N-n;i++)
		addedge(i*2,(i+n)*2-1,oo,s);
	for(int i=1;i<=N;i++)
		addedge(i*2,T,oo,0);
		*/
	solve();
	printf("%d\n",mincost);
//	printf("%d\n",maxflow);
	return 0;
}
