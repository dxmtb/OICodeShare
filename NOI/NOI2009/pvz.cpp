/*
ID: dxmtb
PROG: NOI2009 植物大战僵尸
TIME: 2011.03.14
STATE: Solved
MEMO: 最大权闭合图 + 判环
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN=1000;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *back,*next;
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),back(_back),next(_next){}
	Node(){}
	void *operator new (unsigned ,void *p){return p;}
}pool[MAXN*MAXN*2],*mem=pool,*adj[MAXN];

inline void addedge(int u,int v,int c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;

int lv[MAXN];
bool disable[MAXN];
bool label()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	q.push(S);
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (!disable[p->v] && p->c>0 && lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[T]!=-1)
			return true;
	}
	return lv[T]!=-1;
}

int maxflow;
void augment()
{
	int sta[MAXN]={S},size=1;
	Node *path[MAXN];
	while(size)
	{
		int u=sta[size-1];
		Node *p;
		if (u!=T)
		{
			for(p=adj[u];p;p=p->next)
				if (p->c>0 && lv[p->v]==lv[u]+1)
					break;
			if (p) sta[size]=p->v,path[size++]=p;
			else lv[u]=-1,size--;
		}
		else
		{
			int delta=oo;
			for(int i=size-1;i;i--)
				if (path[i]->c<delta)
					delta=path[i]->c;
			for(int i=size-1;i;i--)
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
				if (path[i]->c==0)
					size=i;
			}
			maxflow+=delta;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

bool vis[MAXN];
int Time,d[MAXN],f[MAXN];
int father[MAXN];
int score[MAXN];
void dfs(int u)
{
	vis[u]=true;
	d[u]=Time++;
	for(Node *p=adj[u];p;p=p->next)
		if (p->c>0)
		{
			if (!vis[p->v])
			{
				father[p->v]=u;
				dfs(p->v);
			}
			else if (!f[p->v])
			{
				for(int i=u;i!=p->v;i=father[i])	
					disable[i]=true;
				disable[p->v]=true;
			}
		}
	f[u]=Time++;
}

void spfa(int s)
{
	queue<int> q;
	q.push(s);
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c==0 && !disable[p->v])
			{
				disable[p->v]=true;
				q.push(p->v);
			}
	}
}

int N,M;
int n[MAXN][MAXN];
int main()
{
	freopen("pvz.in","r",stdin);
	freopen("pvz.out","w",stdout);
	scanf("%d%d",&N,&M);
	S=0;
	int tot=0,sum=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			n[i][j]=++tot;
	T=++tot;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			scanf("%d",score+n[i][j]);
			if (score[n[i][j]]>0) 
				addedge(S,n[i][j],score[n[i][j]]);
			else if (score[n[i][j]]<0)
				addedge(n[i][j],T,-score[n[i][j]]);
			int w;
			scanf("%d",&w);
			while(w--)
			{
				int r,c;
				scanf("%d%d",&r,&c);
				addedge(n[r][c],n[i][j],oo);
			}
		}
	for(int i=0;i<N;i++)
		for(int j=0;j<M-1;j++)
			addedge(n[i][j],n[i][j+1],oo);
	for(int i=0;i<N;i++)
		for(int j=0;j<M-1;j++)
			if (!vis[n[i][j]])
				dfs(n[i][j]);
	for(int i=S+1;i<T;i++)
		if (disable[i])
			spfa(i);
	for(int i=S+1;i<T;i++)
		if (!disable[i] && score[i]>0)
			sum+=score[i];
	dinic();
	printf("%d\n",max(0,sum-maxflow));
	return 0;
}
