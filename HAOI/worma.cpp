/*
ID: dxmtb
PROG: HAOI2009 毛毛虫
TIME: 2011.03.16
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=300005;

struct Node
{
	int v;
	Node *next;
	Node(int _v,Node *_next):
		v(_v),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v)
{
	adj[u]=new Node(v,adj[u]);
	adj[v]=new Node(u,adj[v]);
}

int tot[MAXN],father[MAXN];
int a[MAXN],size;
void dfs(int u)
{
	for(Node *p=adj[u];p;p=p->next)
		if (p->v!=father[u])
		{
			tot[u]++;
			father[p->v]=u;
			dfs(p->v);
		}
	a[size++]=u;
}

int N,M;
int d[MAXN][2];
int main()
{
	freopen("worma.in","r",stdin);
	freopen("worma.out","w",stdout);
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	dfs(1);
	if (size!=N)
		printf("wrong!\n");
	int re=0;
	for(int k=0;k<size;k++)
	{
		int u=a[k];
		d[u][0]=d[u][1]=-0x7fffffff;
		for(Node *p=adj[u];p;p=p->next)
			if (p->v!=father[u])
			{
				int nd;
				if (tot[p->v]) nd=d[p->v][0]+tot[p->v];
				else nd=d[p->v][0]+1;
				if (nd>d[u][0])
				{
					d[u][1]=d[u][0];
					d[u][0]=nd;
				}
				else if (nd>d[u][1])
					d[u][1]=nd;
			}
		if (tot[u]==0)
			d[u][0]=0;
		else if (tot[u]>=2)
		{
			int nre=d[u][0]+d[u][1]+tot[u]-2+(u!=1);
			if (nre>re)
				re=nre;
		}
	}
	printf("%d\n",re+1);
	return 0;
}
