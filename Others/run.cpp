/*
ID: dxmtb
PROG: 晨跑
TIME: 2010.10.9
STATE: Solved
MEMO: 费用流 原始对偶算法 拆点
*/ 
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=500;
const int oo=100000000;

#define min(a,b) ((a)>(b)?(b):(a))

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(int V,int C,int W,Node* N,Node* B=0):v(V),c(C),w(W),next(N),back(B){}
}*adj[MAXN];

int n,m;
int s,t;
int mincost,maxflow;
int piS;

bool vis[MAXN];
bool agu(int u,int delta)
{
	if (u==t) 
		return maxflow+=delta,mincost+=delta*piS,delta;
	vis[u]=true;
	int l=delta;
	for(Node *p=adj[u];p;p=p->next)
		if (p->c&&!vis[p->v]&&!p->w)
		{
			int d=agu(p->v,min(l,p->c));
			p->c-=d;p->back->c+=d;l-=d;
			if (!l) return delta;
		}
	return delta-l;
}

bool modlabel()
{
	deque<int> q;q.push_back(t);
	static int d[MAXN];
	memset(d,0x3f,sizeof(d));d[t]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		int dt;
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c>0&&(dt=d[u]-p->w)<d[p->v])
				(d[p->v]=dt)<=d[q.size()?q.front():0]
					?q.push_front(p->v):q.push_back(p->v);
	}
	for(int i=s;i<=t;++i)
		for(Node *p=adj[i];p;p=p->next)
			p->w+=d[p->v]-d[i];
	piS+=d[s];
	return d[s]<oo;
}

void addedge(int a,int b,int c,int w)
{
//	printf("%d %d %d %d\n",a,b,c,w);
	adj[a]=new Node(b,c,w,adj[a]);
	adj[b]=new Node(a,0,-w,adj[b],adj[a]);
	adj[a]->back=adj[b];
}

int main()
{
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
	scanf("%d%d",&n,&m);
	s=1;t=n*2;
	addedge(s,s+1,oo,0);
	addedge(t-1,t,oo,0);
	for(int i=2;i<n;i++)
		addedge(i*2-1,i*2,1,0);
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		addedge(a*2,b*2-1,1,c);
	}
	while(modlabel())
		do memset(vis,false,sizeof(vis));
		while (agu(s,oo));
	printf("%d %d\n",maxflow,mincost);
	return 0;
}

