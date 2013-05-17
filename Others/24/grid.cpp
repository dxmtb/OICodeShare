/*
ID: dxmtb
PROG: 线性规划与网络流24题 方格取数问题
TIME: 2011.02.02
STATE: Solved
MEMO: 最小割 不能一起连一条边
*/
 include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=1000;
const int oo=0x7fffffff;
const int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int p,int q,Node *m,Node *n=NULL):v(p),c(q),next(m),back(n){}
}*adj[MAXN];

inline void addedge(int u,int v,int c)
{
//	printf("add %d %d %d\n",u,v,c);
	adj[u]=new Node (v,c,adj[u]);
	adj[v]=new Node (u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

#define f(i,j) (i*N+j+1)

int lv[MAXN];
int S,T;
bool label()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	q.push(S);
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&lv[p->v]==-1)
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
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					stack[size]=p->v;
					path[size++]=p;
					break;
				}
			if (!p)
				size--,lv[u]=-1;
		}
		else
		{
			int delta=oo;
			for(int i=size-1;i;i--)
				if (path[i]->c<delta)
					delta=path[i]->c;
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

int N,M,sum;
int map[MAXN][MAXN];
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d%d",&M,&N);
	S=0;T=N*M+1;
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
		{
			scanf("%d",map[i]+j);
			sum+=map[i][j];
		}
	for(int i=0;i<M;i++)
		for(int j=(i&1);j<N;j+=2)
		{
			addedge(S,f(i,j),map[i][j]);
			for(int k=0;k<4;k++)
			{
				int ni=i+way[k][0],nj=j+way[k][1];
				if (ni>=0&&ni<M&&nj>=0&&nj<N)
					addedge(f(i,j),f(ni,nj),oo);
			}
		}
	for(int i=0;i<M;i++)
		for(int j=(i&1)^1;j<N;j+=2)
			addedge(f(i,j),T,map[i][j]);
	dinic();
	printf("%d\n",sum-maxflow);
	return 0;
}
