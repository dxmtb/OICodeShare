/*
ID: dxmtb
PROG: [Usaco2010 Hol]Cowwar 奶牛战争
TIME: 2011.03.29
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int MAXN=3005;
const int oo=~0u>>1;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
}*adj[MAXN];

inline void addedge(int u,int v,int c)
{
	adj[u]=new Node(v,c,adj[u]);
	adj[v]=new Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXN];
bool label()
{
	queue<int> q;
	q.push(S);
	lv[S]=0;
	for(int i=1;i<=T;i++)
		lv[i]=-1;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c && lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[T]!=-1)
			return true;
	}
	return false;
}

inline void Min(int &a,int b)
{
	if (b<a)
		a=b;
}

int maxflow;
void augment()
{
	int stack[MAXN]={S},size=1;
	Node *path[MAXN];
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c && lv[p->v]==lv[u]+1)
				{
					path[size]=p;
					stack[size++]=p->v;
					break;
				}
			if (!p)
				lv[u]=-1,size--;
		}
		else
		{
			int delta=oo;
			for(int i=1;i<size;i++)
				Min(delta,path[i]->c);
			for(int i=size-1;i;i--)
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
				if (path[i]->c==0)
					size=i;
			}
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
char str[MAXN];

int main()
{
	scanf("%d%d",&N,&M);
	scanf(" %s",str+1);
	S=0,T=N*3+1;
	for(int i=1;i<=N;i++)
		if (str[i]=='J')
		{
			addedge(S,i,1);
			addedge(i,i+N,1);
			addedge(i+N,i+N+N,1);
		}
		else if (str[i]=='T')
			addedge(i,T,1);
		else
			addedge(i,i+N,1);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if (str[v]=='J')
			swap(u,v);
		if (str[u]=='J')
		{
			if (str[v]=='T')
				addedge(u+N+N,v,1);
			else if (str[v]=='J')
			{
				addedge(u,v+N,1);
				addedge(v,u+N,1);
			}
			else if (str[v]=='E')
				addedge(u,v,1);
		}
		else if (str[u]=='T')
		{
			if (str[v]=='E')
				addedge(v+N,u,1);
		}
		else 
			if (str[v]=='T')
				addedge(u+N,v,1);
	}
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
