/*
ID: dxmtb1
PROG: race3
LANG: C++
*/
#include <cstdio>
#include <cstring>
const int MAXN=55;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
}*adj[MAXN];

void addedge(int u,int v)
{
	adj[u]=new Node(v,adj[u]);
}

int vis[MAXN];
int N,forbid;
int re[MAXN],tot,tot2;

void dfs(int u)
{
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v]&&p->v!=forbid)
			dfs(p->v);
}

bool flag;
void dfs2(int u,int sta)
{
	vis[u]=sta;
	for(Node *p=adj[u];p&&flag;p=p->next)
	{
		if (vis[p->v]!=0&&vis[p->v]!=sta)
		{
			flag=false;
			return ;
		}
		if (!vis[p->v]&&p->v!=forbid)
			dfs2(p->v,sta);
	}
}

int main()
{
	freopen("race3.in","r",stdin);
	freopen("race3.out","w",stdout);
	while(true)
	{
		int x;
		scanf("%d",&x);
		if (x==-1) break;
		while(x!=-2)
		{
			addedge(N,x);
			scanf("%d",&x);
		}
		N++;
	}
	N--;
	for(int i=1;i<N;i++)
	{
		forbid=i;
		memset(vis,false,sizeof(vis));
		dfs(0);
		if (!vis[N])
			re[tot++]=i;
	}
	printf("%d",tot);
	for(int i=0;i<tot;i++)
		printf(" %d",re[i]);
	printf("\n");
	for(int i=1;i<N;i++)
	{
		flag=true;
		forbid=i;
		memset(vis,false,sizeof(vis));
		dfs2(0,1);
		dfs2(i,2);
		if (flag)
			re[tot2++]=i;
	}
	printf("%d",tot2);
	for(int i=0;i<tot2;i++)
		printf(" %d",re[i]);
	printf("\n");
	return 0;
}
