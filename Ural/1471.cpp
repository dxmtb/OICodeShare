/*
ID: dxmtb
PROG: Ural 1471 Tree
TIME: 2010.4.15
STATE: Solved
MEMO: LCAŒ Ã‚ TarjanÀ„∑®
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=50000,MAXM=75000;

struct Node
{
	int v,w;
	Node *next;
	Node(int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
}*edge[MAXN],*query[MAXM];

int n,m,ans[MAXM],father[MAXN],dis[MAXN];

void init()
{
	memset(edge,0,sizeof(edge));
	memset(query,0,sizeof(query));
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		edge[x]=new Node(y,w,edge[x]);
		edge[y]=new Node(x,w,edge[y]);
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		query[x]=new Node(y,i,query[x]);
		query[y]=new Node(x,i,query[y]);
	}
}

int find(int u)
{
	if (father[u]==u)return u;
	return father[u]=find(father[u]);
}

void Union(int u,int v)
{
	father[u]=find(v);
}

void lca(int u)
{
	static bool visited[MAXN],color[MAXN];	
	father[u]=u;
	visited[u]=true;
	for(Node *p=edge[u];p;p=p->next)
	if(!visited[p->v])
	{
		dis[p->v]=dis[u]+p->w;
		lca(p->v);
		Union(p->v,u);
	}
	color[u]=true;
	for(Node *p=query[u];p;p=p->next)
		if (color[p->v])
			ans[p->w]=dis[u]+dis[p->v]-2*dis[find(p->v)];
}

int main() 
{
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	init();
	lca(0);
	for(int i=0;i<m;i++)printf("%d\n",ans[i]);
    return 0;
}
