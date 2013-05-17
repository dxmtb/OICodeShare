/*
 * Problem: 1116: [POI2008]CLO
 * Time: 2011.07.20
 * Author: dxmtb
 * State: Solved
 * Memo: 没有树
*/
#include <cstdio>

const int MAXN=100005,MAXM=200005;

struct Node
{
	int v;
	Node *next;
	Node (){}
	Node (int _v,Node *_next):v(_v),next(_next){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXM*2],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	adj[v]=new (mem++)Node(u,adj[v]);
}

bool vis[MAXN];
int V,E;
void dfs(int u)
{
	vis[u]=true;
	V++;
	for(Node *p=adj[u];p;p=p->next)
	{
		E++;
		if (!vis[p->v])
			dfs(p->v);
	}
}

int N,M;
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	for(int i=1;i<=N;i++)
		if (!vis[i])
		{
			V=0,E=0;
			dfs(i);
			if (2*(V-1)==E)
			{
				printf("NIE\n");
				return 0;
			}
		}
	printf("TAK\n");
	return 0;
}
