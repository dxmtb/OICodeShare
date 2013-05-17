/*
ID: dxmtb
PROG: ural1076 trash
TIME: 2010.02.20
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN=305;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node*_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*MAXN*2],*mem=pool;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,piS,N;
bool label()
{
	deque<int> q;
	int dis[MAXN];
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[T]=0;
	q.push_back(T);
	while(q.size())
	{
		int u=q.front();q.pop_front();
		int dt;
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && dis[p->v] > (dt=dis[u]-p->w))
			{
				dis[p->v]=dt;
				if (q.empty() || dt>dis[q.front()])
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

bool v[MAXN];
int mincost;
int augment(int u,int m)
{
	if (u==T) return mincost+=piS*m,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (p->c && !p->w && !v[p->v])
		{
			v[p->v]=true;
			int d=augment(p->v,min(p->c,l));
			l-=d;	
			p->c-=d,p->back->c+=d;
			if (!l) return m;
		}
	return m-l;
}

void solve()
{
	while(label())
		do memset(v,false,sizeof(v));
		while(augment(S,oo));
}

int a[MAXN][MAXN];
int sum[MAXN];
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			scanf("%d",a[i]+j);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			sum[i]+=a[j][i];
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			addedge(i,j+N,1,sum[i]-a[j][i]);
	S=0,T=N+N+1;
	for(int i=1;i<=N;i++)
	{
		addedge(S,i,1,0);
		addedge(i+N,T,1,0);
	}
	solve();
	printf("%d\n",mincost);
	return 0;
}
