/*
ID: dxmtb
PROG: NOI2008 志愿者招募
TIME: 2011.03.31
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN=2005;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node (){}
	Node (int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*20],*mem=pool;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,N,M;
int A[MAXN];
int dis[MAXN];
int piS;

bool label()
{
	deque<int> q;
	q.push_back(T);
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[T]=0;
	while(q.size())
	{
		int u=q.front();
		int t;
		q.pop_front();
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && dis[p->v]>(t=dis[u]+p->back->w))
			{
				dis[p->v]=t;
				if (q.empty() || t<dis[q.front()])
					q.push_front(p->v);
				else 
					q.push_back(p->v);
			}
	}
	for(int u=S;u<=T;u++)
		for(Node *p=adj[u];p;p=p->next)
			p->back->w=p->back->w+dis[u]-dis[p->v];
	piS+=dis[S];
	return dis[S]!=oo;
}

bool vis[MAXN];
int mincost;
int augment(int u,int m)
{
	vis[u]=true;
	if (u==T) return mincost+=m*piS,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (p->c && !p->w && !vis[p->v])
		{
			int t=augment(p->v,min(m,p->c));
			p->c-=t,p->back->c+=t;
			l-=t;
			if (!l)
				return m;
		}
	return m-l;
}

void solve()
{
	while(label())
		do memset(vis,false,sizeof(vis));
		while (augment(S,oo));
}

int main()
{
	freopen("employee.in","r",stdin);
	freopen("employee.out","w",stdout);
	int N,M;
	scanf("%d%d",&N,&M);
	S=0,T=N+2;
	for(int i=2;i<=N+1;i++)
		scanf("%d",A+i);
	for(int i=1;i<=M;i++)
	{
		int S,T,C;
		scanf("%d%d%d",&S,&T,&C);
		S++,T++;
		addedge(S-1,T,oo,C);
	}
	for(int i=1;i<=N+1;i++)
	{
		int t=A[i]-A[i+1];
		if (t>0)
			addedge(i,T,t,0);
		else
			addedge(S,i,-t,0);
	}
	for(int i=1;i<=N;i++)
		addedge(i+1,i,oo,0);
	solve();
	printf("%d\n",mincost);
	return 0;
}
