/*
 * Problem: Çë¿Í
 * Time: 2011.04.13
 * Author: dxmtb
 * State: UNSolved
 * Memo: No Special Judge
*/
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

const int MAXN=5000;
const int oo=~0u>>2;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
}*adj[MAXN],*left[MAXN];

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
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
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
		left[i]=adj[i];
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			for(Node *&p=left[u];p;p=p->next)
				if (p->c>0 && lv[p->v]==lv[u]+1)
				{
					path[size]=p;
					stack[size++]=p->v;
					break;
				}
			if (!left[u])
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
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
			}
			maxflow+=delta;
			size=k;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

int N,M;
void print()
{
	if (maxflow<M)
		printf("-1\n");
	else
	{
		for(int i=N+1;i<=N+M;i++)
			for(Node *p=adj[i];p;p=p->next)
				if (p->c==1 && p->v>=1 && p->v<=N)
				{
					printf("%d\n",p->v);
					break;
				}
	}
}

long double take[MAXN];
int will[MAXN];

int main()
{
	freopen("cookie.in","r",stdin);
	freopen("cookie.out","w",stdout);
	scanf("%d%d",&N,&M);
	S=0;T=N+M+1;
	for(int i=1;i<=M;i++)
	{
		int tot;
		scanf("%d",&tot);
		if (tot==0)
		{
			printf("-1\n");
			return 0;
		}
		long double tmp=1.0/tot;
		for(int j=0;j<tot;j++)
		{
			int x;
			scanf("%d",&x);
			take[x]+=tmp;
			addedge(x,N+i,1);
		}
	}
	for(int i=1;i<=N;i++)
	{
		will[i]=int(ceil(take[i]));
		addedge(S,i,will[i]);
	}
	for(int i=N+1;i<=N+M;i++)
		addedge(i,T,1);
	dinic();
	print();
	return 0;
}
