/*
 * Problem: NOI2010 航空管制
 * Time: 2011.05.18
 * Author: dxmtb
 * State: Solved
 * Memo: 拓扑排序 贪心
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAXN=2005;
const int MAXM=10005;

struct Node
{
	int v;
	Node *next;
	Node(int _v,Node *_next):
		v(_v),next(_next){}
	Node(){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXM],*mem=pool;

int in[MAXN];
inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	in[v]++;
}

bool vis[MAXN];
int K[MAXN];
void dfs(int u)
{
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
	{
		assert(!vis[p->v]);
		if (K[u]-1<K[p->v])
			K[p->v]=K[u]-1;
		in[p->v]--;
		if (in[p->v]==0)
			dfs(p->v);
	}
}

int dfs2(int u)
{
	vis[u]=true;
	int tot=1;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v])
			tot+=dfs2(p->v);
	return tot;
}

inline bool cmp(const int &a,const int &b)
{
	return K[a]<K[b];
}

int N,M;
int a[MAXN],pos[MAXN];
int main()
{
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		scanf("%d",K+i);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(v,u);
	}
	for(int i=1;i<=N;i++)
		if (!vis[i] && in[i]==0)
			dfs(i);
	for(int i=1;i<=N;i++)
		a[i]=i;
	sort(a+1,a+1+N,cmp);
	for(int i=1;i<=N;i++)
		pos[a[i]]=i;
/*	printf("%d",a[0]);
	for(int i=1;i<N;i++)
		printf(" %d",a[i]);
	printf("\n");*/
	bool first=true;
	for(int i=1;i<=N;i++)
	{
		memset(vis,false,sizeof(vis));
		int re,tot;
		re=tot=dfs2(i);
		for(int j=1;j<=N;j++)
		{
			if (!vis[a[j]])
			{
				tot++;
				if (K[a[j]]<=re)
					re++;
				else if (K[a[j]]<tot)
					re=K[a[j]]+1;
			}
		}
		if (first) first=false;
		else printf(" ");
		printf("%d",re);
	}
	printf("\n");
	return 0;
}
