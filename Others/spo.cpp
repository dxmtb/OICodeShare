/*
 * Problem: POI2001 和平委员会
 * Time: 2011.04.07
 * Author: dxmtb
 * State: Solved
 * Memo: 2-SAT
*/
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=20000;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node (){}
	void *operator new (unsigned,void *p){return p;}
}*adj[MAXN],*adj2[MAXN],pool[MAXN*5],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
}

inline void addedge2(int u,int v)
{
	if (u==v)
		return ;
	adj2[u]=new (mem++)Node(v,adj2[u]);
}

vector<int> rv[MAXN];
int tot;
int s[MAXN],size,to[MAXN];
int up[MAXN],dfn[MAXN];
bool vis[MAXN],in[MAXN],used[MAXN];
int ind;
void dfs(int u)
{
	up[u]=dfn[u]=++ind;
	s[size++]=u;
	in[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!dfn[p->v])
		{
			dfs(p->v);
			if (up[p->v]<up[u])
				up[u]=up[p->v];
		}
		else if (in[p->v] && dfn[p->v]<up[u])
			up[u]=dfn[p->v];
	if (up[u]==dfn[u])
	{
		memset(used,false,sizeof(used));
		int v;
		do
		{
			v=s[--size];
			in[v]=false;
			to[v]=tot;
			rv[tot].push_back(v);
			if (used[v/2])
			{
				printf("NIE\n");
				exit(0);
			}
			used[v/2]=true;
		}while(v!=u);
		tot++;
	}
}

void topo(int u)
{
	for(Node *p=adj2[u];p;p=p->next)
		if (!vis[p->v])
			topo(p->v);
	vis[u]=true;
	s[size++]=u;
}

int N,M;
int main()
{
	freopen("spo.in","r",stdin);
	freopen("spo.out","w",stdout);
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		a--,b--;
		addedge(a,b/2*4+1-b);
		addedge(b,a/2*4+1-a);
	}
	memset(to,-1,sizeof(to));
	for(int i=0;i<N*2;i++)
		if (!dfn[i])
		{
			size=0;
			dfs(i);
			assert(size==0);
		}
	for(int i=0;i<N*2;i++)
		for(Node *p=adj[i];p;p=p->next)
			addedge2(to[i],to[p->v]);
	memset(used,false,sizeof(used));
	size=0;
	for(int i=0;i<tot;i++)
		if (!vis[i])
			topo(i);
	memset(vis,false,sizeof(vis));
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<(int)rv[s[i]].size();j++)
		{
			int v=rv[s[i]][j];
			if (used[v/2])
				goto OUT;
		}
		for(int j=0;j<(int)rv[s[i]].size();j++)
		{
			int v=rv[s[i]][j];
			used[v/2]=true;
			vis[v]=true;
		}
OUT:;
	}
	for(int i=0;i<2*N;i++)
		if (vis[i])
			printf("%d\n",i+1);
	return 0;
}
