/*
ID: dxmtb
PROG: 悠闲的漫步
TIME: 2010.9.4
STATE: Solved
MEMO: dfs
*/
#include <cstdio>
//#define NODEBUG
#include <assert.h>
using namespace std;

const int MAXN=2005;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
};

Node *adj[MAXN];
int top,p,re;
bool vis[MAXN];

void dfs(int now,int dep)
{
	vis[now]=true;
	if (now>=p&&dep>re)
		re=dep;
	for(Node *p=adj[now];p;p=p->next)
		if (!vis[p->v])
			dfs(p->v,dep+1);
}

inline void add(int a,int b)
{
	adj[a]=new Node(b,adj[a]);
	adj[b]=new Node(a,adj[b]);
}

int main()
{
	freopen("stroll.in","r",stdin);
	freopen("stroll.out","w",stdout);
	scanf("%d",&p);
	top=p;
	for(int i=1,a,b,c;i<p;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		assert(top<=2*p);
		if (b)add(a,b);
		else add(a,top++);
		if (c)add(a,c);
		else add(a,top++);
	}
	dfs(1,0);
	printf("%d\n",re);
	return 0;
}


