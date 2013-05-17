/*
ID: dxmtb
PROG: 线性规划与网络流24题 负载平衡问题
TIME: 2011.02.11
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=105;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
}*adj[MAXN],pool[MAXN*10],*mem=pool;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,N,piS,mincost;
bool v[MAXN];
bool label()
{
	deque<int> q;
	int dis[MAXN];
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[T]=0;q.push_back(T);
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
	for(int u=S;u<=T;u++)
		for(Node *p=adj[u];p;p=p->next)
			p->w+=dis[p->v]-dis[u];
	piS+=dis[S];
	return dis[S]<oo;
}

int augment(int u,int m)
{
	if (u==T) return mincost+=piS*m,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (!v[p->v]&&!p->w&&p->c)
		{
			v[p->v]=true;
			int d=augment(p->v,min(p->c,l));
			l-=d;
			p->c-=d,p->back->c+=d;
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

int main()
{
	freopen("move.in","r",stdin);
	freopen("move.out","w",stdout);
	scanf("%d",&N);
	S=0;T=N+1;
	int s[MAXN],average=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d",s+i);
		average+=s[i];
	}
	average/=N;
	for(int i=1;i<N;i++)
	{
		addedge(i,i+1,oo,1);
		addedge(i+1,i,oo,1);
	}
	addedge(N,1,oo,1);
	addedge(1,N,oo,1);
	for(int i=1;i<=N;i++)
		if (s[i]>average)
			addedge(S,i,s[i]-average,0);
		else if (s[i]<average)
			addedge(i,T,average-s[i],0);
	solve();
	printf("%d\n",mincost);
	return 0;
}
