/*
ID: dxmtb
PROG: [ZJOI2007]矩阵游戏
TIME: 2011.03.31
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <cstring>

const int MAXN=500;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
	Node(){}
	void *operator new (unsigned,void *p){return p;}
}*adj[MAXN],*cur[MAXN],pool[MAXN*MAXN],*mem;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,1,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXN];
bool label()
{
	int Q[MAXN],l,r;
	Q[l=r=0]=S;
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	while(l<=r)
	{
		int u=Q[l++];
		for(Node *p=adj[u];p;p=p->next)
			if (p->c && lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				Q[++r]=p->v;
			}
		if (lv[T]!=-1)
			return true;
	}
	return false;
}

int maxflow;
void augment()
{
	int sta[MAXN]={S},size=1;
	for(int i=S;i<=T;i++)
		cur[i]=adj[i];
	Node *path[MAXN];
	while(size)
	{
		int u=sta[size-1];
		if (u!=T)
		{
			for(Node *&p=cur[u];p;p=p->next)
				if (p->c && lv[p->v]==lv[u]+1)
				{
					path[size]=p;
					sta[size++]=p->v;
					break;
				}
			if (!cur[u])
				lv[u]=-1,size--;
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
			size=k;
			maxflow+=delta;
		}
	}
}

void dinic()
{
	maxflow=0;
	while(label())
		augment();
}

int N;
int main()
{
	freopen("1059.in","r",stdin);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		mem=pool;
		scanf("%d",&N);
		S=0,T=2*N+1;
		for(int i=S;i<=T;i++)
			adj[i]=NULL;
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				int x;
				scanf("%d",&x);
				if (x)
					addedge(i,j+N);
			}
		for(int i=1;i<=N;i++)
		{
			addedge(S,i);
			addedge(i+N,T);
		}
		dinic();
		if (maxflow==N) printf("Yes\n");
		else printf("No\n");
//		printf("%d\n",maxflow);
	}
	return 0;
}
