/*
ID: dxmtb
PROG: 线性规划与网络流24题 最长递增子序列问题
TIME: 2011.02.02
STATE: Solved
MEMO: 网络流 分层
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=250000;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int p,int q,Node *m,Node *n=NULL):v(p),c(q),next(m),back(n){}
}*adj[MAXN];

inline void addedge(int u,int v,int c)
{
	adj[u]=new Node(v,c,adj[u]);
	adj[v]=new Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int N,re1,re2,re3;
int S,T;
int a[MAXN],d[MAXN];

int lv[MAXN];
bool label()
{
	queue<int> q;
	q.push(S);
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[T]!=-1)
			return true;
	}
	return false;
}

int maxflow;
void augment()
{
	int stack[MAXN]={S},size=1;
	Node *path[MAXN];
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					path[size]=p;
					stack[size++]=p->v;
					break;
				}
			if (!p)
				size--,lv[u]=-1;
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
				if (!path[i]->c)
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

int main()
{
	freopen("alis.in","r",stdin);
	freopen("alis.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",a+i);
	for(int i=1;i<=N;i++)
	{
		d[i]=1;
		for(int j=1;j<i;j++)
			if (a[j]<=a[i]&&d[i]<d[j]+1)
			{
				d[i]=d[j]+1;
			}
		if (d[i]>re1)
			re1=d[i];
	}
	printf("%d\n",re1);
	S=0,T=N*re1+1;
	for(int i=1;i<=N;i++)
		addedge(S,i,1);
	for(int i=1;i<=N;i++)
		addedge(N*(re1-1)+i,T,1);
	for(int i=1;i<=N;i++)
		for(int j=1;j<i;j++)
		if (a[j]<=a[i]&&d[i]==d[j]+1)
			for(int k=1;k<re1;k++)
				addedge(N*(k-1)+j,N*k+i,1);
	dinic();
	printf("%d\n",maxflow);
	addedge(S,1,oo);
	addedge(N*re1,T,oo);
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
