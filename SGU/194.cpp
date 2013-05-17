/*
 * Problem: sgu194 Reactor Cooling
 * Time: 2011.07.07
 * Author: dxmtb
 * State: Solved
 * Memo: 上下界网络流可行流
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=205,MAXM=(MAXN*MAXN+MAXN)*2;
const int oo=~0u>>1;

struct Node
{
	int v,c,f;
	Node *next,*back;
	Node (){}
	Node (int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),f(0),next(_next),back(_back){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],*cur[MAXN],pool[MAXM],*mem=pool;

inline void addedge(int u,int v,int c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int N,M;
int S,T;
int Ms[MAXN];
int B[MAXM];

int lv[MAXN];
bool label()
{
	queue<int> q;
	for(int i=S;i<=T;i++)
		lv[i]=-1;
	lv[S]=0;
	q.push(S);
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>p->f && lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
	}
	return lv[T]!=-1;
}

int sta[MAXN],size;
Node *path[MAXN];
void augment()
{
	for(int i=S;i<=T;i++)
		cur[i]=adj[i];
	sta[0]=S;
	size=1;
	while(size)
	{
		int u=sta[size-1];
		if (u!=T)
		{
			for(Node *&p=cur[u];p;p=p->next)
				if (p->c>p->f && lv[p->v]==lv[u]+1)
				{
					sta[size]=p->v;
					path[size++]=p;
					break;
				}
			if (cur[u]==NULL)
				lv[u]=-1,size--;
		}
		else
		{
			int delta=oo,t,j=-1;
			for(int i=size-1;i;i--)
			{
				if ((t=path[i]->c-path[i]->f)<delta)
					delta=t,j=i;
			}
			for(int i=size-1;i;i--)
				path[i]->f+=delta,path[i]->back->f-=delta;
			size=j;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

int main()
{
	scanf("%d%d",&N,&M);
	S=0,T=N+1;
	for(int i=0;i<M;i++)
	{
		int u,v,b,c;
		scanf("%d%d%d%d",&u,&v,&b,&c);
		if (b>c)
		{
			printf("NO\n");
			return 0;			
		}
		B[i]=b;
		Ms[u]+=b;
		Ms[v]-=b;
		addedge(u,v,c-b);
	}
	for(int i=1;i<=N;i++)
		if (Ms[i]>0)
			addedge(i,T,Ms[i]);
		else if (Ms[i]<0)
			addedge(S,i,-Ms[i]);
	dinic();
	for(Node *p=adj[S];p;p=p->next)
		if (p->c!=p->f)
		{
			printf("NO\n");
			return 0;
		}
	printf("YES\n");
	for(int i=0;i<M;i++)
		printf("%d\n",pool[2*i].f+B[i]);
	return 0;
}
