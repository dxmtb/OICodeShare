/*
ID: dxmtb
PROG: 线性规划与网络流24题 分配问题
TIME: 2011.02.11
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN=10000;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
	Node(){}
	void * operator new (unsigned,void *p){return p;}
}*adj[MAXN],pool[MAXN*2],*mem;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,piS,mincost;
bool label()
{
	int dis[MAXN];
	deque<int> q;
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	q.push_back(T);dis[T]=0;
	while(q.size())
	{
		int u=q.front();q.pop_front();
		int dt;
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && dis[p->v]>(dt=dis[u]-p->w))
			{
				dis[p->v]=dt;
				if (q.empty()||dt>dis[q.front()])
					q.push_back(p->v);
				else q.push_front(p->v);
			}
	}
	for(int i=S;i<=T;i++)
		for(Node *p=adj[i];p;p=p->next)
			p->w+=dis[p->v]-dis[i];
	piS+=dis[S];
	return dis[S]<oo;
}

bool v[MAXN];
int augment(int u,int m)
{
	if (u==T) return mincost+=piS*m,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (!v[p->v] && p->c && !p->w)
		{
			v[p->v]=true;
			int d=augment(p->v,min(l,p->c));
			l-=d;
			p->c-=d;p->back->c+=d;
			if (!l)
				break;
		}
	return m-l;
}

void solve()
{
	while(label())
		do memset(v,false,sizeof(v));
		while(augment(S,oo));
}

int N,M;
int c[MAXN][MAXN];
int main()
{
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	scanf("%d",&N);
	M=N;
	S=0,T=N+N+1;
	for(int i=1;i<=N;i++)
		for(int j=N+1;j<T;j++)
			scanf("%d",c[i]+j);
	for(int rule=0;rule<2;rule++)
	{
		int tmp=rule?-1:1;
		memset(adj,0,sizeof(adj));
		mem=pool;mincost=0;piS=0;
		for(int i=1;i<=N;i++)
			addedge(S,i,1,0);
		for(int i=N+1;i<T;i++)
			addedge(i,T,1,0);
		for(int i=1;i<=M;i++)
			for(int j=M+1;j<T;j++)
				addedge(i,j,1,c[i][j]*tmp);
		solve();
		if (rule) printf("%d\n",-mincost);
		else printf("%d\n",mincost);
	}
	return 0;
}

