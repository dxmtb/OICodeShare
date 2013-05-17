/*
 * Problem: 4206. Fast Maximum Matching
 * Time: 2011.07.23
 * Author: dxmtb
 * State: Solved
 * Memo: Hopcroft-Karp
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=100005,MAXM=150005;
const int oo=~0u>>2;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXM*2],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
}

int N,N2;
int mat[MAXN],dis[MAXN];

bool label()
{
	queue<int> q;
	for(int i=1;i<=N;i++)
		if (mat[i]==0)
		{
			dis[i]=0;
			q.push(i);
		}
		else
			dis[i]=oo;
	dis[0]=oo;
	while(q.size())
	{
		int u=q.front(),v;q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (dis[v=mat[p->v]]==oo)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		if (dis[0]!=oo)
			return true;
	}
	return false;
}

bool dfs(int u)
{
	for(Node *p=adj[u];p;p=p->next)
		if (dis[mat[p->v]]==dis[u]+1)
			if (mat[p->v]==0 || dfs(mat[p->v]))
			{
				mat[u]=p->v;
				mat[p->v]=u;
				return true;
			}
	dis[u]=oo;
	return false;
}

void Hopcroft()
{
	for(int i=1;i<=N+N2;i++)
		mat[i]=0;
	int re=0;
	while(label())
		for(int i=1;i<=N;i++)
			if (mat[i]==0 && dfs(i))
				re++;
	printf("%d\n",re);
}

int main()
{
	int M;
	scanf("%d%d%d",&N,&N2,&M);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v+N);
	}
	Hopcroft();
	return 0;
}
