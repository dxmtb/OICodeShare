/*
ID: dxmtb
PROG: 备用交换机
TIME: 2010.9.6
STATE: Solved
MEMO: 求割点
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=105;
const int root=0;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
}*adj[MAXN];

int n,re;

inline void add(int a,int b)
{
//	printf("%d %d\n",a,b);
	adj[a]=new Node(b,adj[a]);
	adj[b]=new Node(a,adj[b]);
}

int color[MAXN];//0 not visited 1 not finished 2 finished
bool cut[MAXN];
int anc[MAXN],depth[MAXN];

void dfs(int u,int father)
{
	int tot=0;
	color[u]=1;depth[u]=depth[father]+1;
	anc[u]=depth[u];
	for(Node *p=adj[u];p;p=p->next)
	{
		if (p->v!=father&&color[p->v]==1)
			anc[u]=min(anc[u],depth[p->v]);
		if (!color[p->v])
		{
			dfs(p->v,u);
			tot++;anc[u]=min(anc[u],anc[p->v]);
			if ((u==root&&tot>1)||(u!=root&&anc[p->v]>=depth[u]))
					cut[u]=true;
		}
	}
	color[u]=2;
}

int main()
{
	freopen("gd.in","r",stdin);
	freopen("gd.out","w",stdout);
	scanf("%d",&n);
	for(int a,b;scanf("%d%d",&a,&b)!=EOF;add(--a,--b));
	dfs(0,0);
	for(int i=0;i<n;i++)
		if (cut[i])
			re++;
	printf("%d\n",re);
	for(int i=0;i<n;i++)
		if (cut[i])
			printf("%d\n",i+1);
	return 0;
}
