/*
ID: dxmtb
PROG: 线性规划与网络流24题 数字梯形问题
TIME: 2011.02.10
STATE: Solved
MEMO: 费用流
*/
 #include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=1000;
const int oo=0x7fffffff;
const int way[3][2]={{1,1},{oo,1},{oo,oo}};

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
	void *operator new(unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*5],*mem;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new (mem++)Node(v,c,w,adj[u]);
	adj[v]=new (mem++)Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int piS,S,T;
bool label()
{
	deque<int> q;
	int dis[MAXN];
	q.push_back(T);
	for(int i=S;i<T;i++)
		dis[i]=oo;
	dis[T]=0;
	while(q.size())
	{
		int u=q.front(),dt;q.pop_front();
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && (dt=dis[u]-p->w)<dis[p->v])
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

int mincost;
bool v[MAXN];
int agument(int u,int m)
{
	if (u==T)
		return mincost+=m*piS,m;
	else
	{
		int l=m;
		for(Node *p=adj[u];p;p=p->next)
			if (!v[p->v] && p->c && !p->w)
			{
				v[p->v]=true;
				int d=agument(p->v,min(l,p->c));
				l-=d;
				p->c-=d;p->back->c+=d;
				if (!l)
					break;
			}
		return m-l;
	}
}

void solve()
{
	while(label())
		do memset(v,0,sizeof(v));
		while(agument(S,oo));
}

int N,M;
int g[MAXN][MAXN];
int La[MAXN][MAXN];

int main()
{
	freopen("digit.in","r",stdin);
	freopen("digit.out","w",stdout);
	scanf("%d%d",&M,&N);
	for(int i=0;i<N;i++)
		for(int j=0;j<M+i;j++)
			scanf("%d",g[i]+j);
	for(int rule=0;rule<3;rule++)
	{
		memset(adj,0,sizeof(adj));
		mem=pool;
		mincost=0;piS=0;
		int t1=way[rule][0],t2=way[rule][1];
		for(int i=0;i<M;i++)
			addedge(S,i*2+1,1,0);
		S=0,T=1;
		for(int i=0;i<N;i++)
			for(int j=0;j<M+i;j++,T+=2)
			{	
				La[i][j]=T;
				addedge(La[i][j],La[i][j]+1,t1,-g[i][j]);
			}
		for(int i=0;i<N-1;i++)
			for(int j=0;j<M+i;j++)
			{
				addedge(La[i][j]+1,La[i+1][j],t2,0);	
				addedge(La[i][j]+1,La[i+1][j+1],t2,0);
			}
		for(int i=0;i<M+N-1;i++)
			addedge(La[N-1][i]+1,T,t1,0);
		solve();
		printf("%d\n",-mincost);
	}
	return 0;
}
