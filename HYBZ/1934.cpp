/*
 * Problem: [Shoi2007]Vote 善意的投票 
 * Time: 2011.04.13
 * Author: dxmtb
 * State: Solved
 * Memo: 最小割
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN=400;
const int oo=~0u>>2;

struct Node
{
	int v,c;
	Node *next,*back;
	Node (int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
	Node(){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],*last[MAXN],pool[MAXN*MAXN],*mem=pool;

inline void addedge(int u,int v,int c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXN];
bool label()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	q.push(S);
	while(q.size())
	{
		int u=q.front();
		q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (lv[p->v]==-1 && p->c>0)
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
	for(int i=S;i<=T;i++)
		last[i]=adj[i];
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			for(Node *&p=last[u];p;p=p->next)
				if (p->c>0 && lv[p->v]==lv[u]+1)
				{
					path[size]=p;
					stack[size++]=p->v;
					break;
				}
			if (last[u]==NULL)
				size--,lv[u]=-1;
		}
		else
		{
			int delta=oo,k;
			for(int i=size-1;i;i--)
				if (path[i]->c<delta)
				{
					delta=path[i]->c;
					k=i;
				}
			for(int i=size-1;i;i--)
				path[i]->c-=delta,
				path[i]->back->c+=delta;
			size=k;
			maxflow+=delta;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

int N,M;
int main()
{
	freopen("1934.in","r",stdin);
	scanf("%d%d",&N,&M);
	S=0,T=N+1;
	for(int i=1;i<=N;i++)
	{
		int x;
		scanf("%d",&x);
		if (x) addedge(S,i,1);
		else addedge(i,T,1);
	}
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v,1);
		addedge(v,u,1);
	}
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
