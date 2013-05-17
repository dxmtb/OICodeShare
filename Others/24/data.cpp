/*
ID: dxmtb
PROG: 线性规划与网络流24题 试题库问题
TIME: 2011.02.02
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=3000;
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

int S,T;

int lv[MAXN];
bool label()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	q.push(S);lv[S]=0;
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
					stack[size]=p->v;
					path[size++]=p;
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

int N,K,M;
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d%d",&K,&N);
	S=0,T=N+K+1;
	for(int i=1;i<=K;i++)
	{
		int a;
		scanf("%d",&a);
		addedge(S,i,a);
		M+=a;
	}
	for(int i=K+1;i<=K+N;i++)
	{
		int p;
		scanf("%d",&p);
		while(p--)
		{
			int a;
			scanf("%d",&a);
			addedge(a,i,1);
		}
		addedge(i,T,1);
	}
	dinic();	
	if (maxflow==M)
	{
		for(int i=1;i<=K;i++)
		{
			printf("%d:",i);
			for(Node *p=adj[i];p;p=p->next)
				if (p->c==0&&p->v>=K+1&&p->v<=K+N)
					printf(" %d",p->v-K);
			printf("\n");
		}
	}
	else printf("No Solution!\n");
	return 0;
}
