/*
ID: dxmtb
PROG: 线性规划与网络流24题 深海机器人问题
TIME: 2011.02.11
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN=2000;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
}*adj[MAXN],pool[MAXN*5],*mem=pool;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,mincost,piS;
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

bool v[MAXN];
int augment(int u,int m)
{
	if (u==T) return mincost+=piS*m,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (!v[p->v] && !p->w &&p->c)
		{
			v[p->v]=true;
			int d=augment(p->v,min(l,p->c));
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
		while (augment(S,oo));
}

int La[MAXN][MAXN];
int main()
{
	freopen("robo.in","r",stdin);
	freopen("robo.out","w",stdout);
	int a,b,P,Q;
	scanf("%d%d",&a,&b);
	scanf("%d%d",&P,&Q);
	int k=1;
	for(int i=0;i<P+1;i++)
		for(int j=0;j<Q+1;j++)
			La[i][j]=k++;
	S=0;T=k;	
	for(int i=0;i<P+1;i++)
		for(int j=0;j<Q;j++)
		{
			int a;
			scanf("%d",&a);
			addedge(La[i][j],La[i][j+1],1,-a);
			addedge(La[i][j],La[i][j+1],oo,0);
		}
	for(int j=0;j<Q+1;j++)
		for(int i=0;i<P;i++)
		{
			int a;
			scanf("%d",&a);
			addedge(La[i][j],La[i+1][j],1,-a);
			addedge(La[i][j],La[i+1][j],oo,0);
		}
	while(a--)
	{
		int c,x,y;
		scanf("%d%d%d",&c,&x,&y);
		addedge(S,La[x][y],c,0);
	}
	while(b--)
	{
		int c,x,y;
		scanf("%d%d%d",&c,&x,&y);
		addedge(La[x][y],T,c,0);
	}
	solve();
	printf("%d\n",-mincost);
	return 0;
}
