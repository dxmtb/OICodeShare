/*
 * Problem: NOI2010 海拔
 * Time: 2011.05.18
 * Author: dxmtb
 * State: Solved
 * Memo: 最小割 + 最短路
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=505,MAXT=(MAXN+1)*(MAXN+1),MAXM=2*MAXN*(MAXN+1);
const int oo=~0u>>1;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXT],pool[MAXM*2],*mem=pool;

void addedge(int u,int v,int w)
{
	adj[u]=new (mem++)Node(v,w,adj[u]);
}

int dis[MAXT];
struct Heap//min first
{
	int a[MAXT],b[MAXT],size;
	void make_heap(int S,int T)
	{
		for(int i=S;i<=T;i++)
		{
			b[i]=i+1;
			a[i+1]=i;
		}
		size=T+1;
	}
	int getmin()
	{
		return a[1];
	}
	void aswap(int u,int v)
	{
		swap(b[a[u]],b[a[v]]);
		swap(a[u],a[v]);
	}
	void down(int i)
	{
		while(i*2<=size)
		{
			int j=2*i;
			if (j+1<=size && dis[a[j]]>dis[a[j+1]])
				j++;
			if (dis[a[i]]>dis[a[j]])
				aswap(i,j);
			else
				break;
			i=j;
		}
	}
	void up(int i)
	{
		while(i!=1)
		{
			int j=i/2;
			if (dis[a[i]]<dis[a[j]])
				aswap(i,j);
			else
				break;
			i=j;
		}
	}
	void dec(int u)
	{
		up(b[u]);
	}
	void pop()
	{
		aswap(1,size);
		size--;
		down(1);
	}
}heap;

bool sure[MAXN];
int S,T;
void dijkstra()
{
	for(int i=S;i<=T;i++)
	{
		dis[i]=oo;
		sure[i]=false;
	}
	dis[S]=0;
	sure[S]=true;
	heap.make_heap(S,T);
	while(true)
	{
		int u=heap.getmin();
		sure[u]=true;
		if (u==T)
			break;
		heap.pop();
		if (dis[u]<dis[T])
		for(Node *p=adj[u];p;p=p->next)
			if (!sure[p->v] && dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				heap.dec(p->v);
			}
	}
	printf("%d\n",dis[T]);
}

int N;
int n[MAXN][MAXN];
int main()
{
	freopen("altitude.in","r",stdin);
	freopen("altitude.out","w",stdout);
	scanf("%d",&N);
	int tot=0;
	S=tot++;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			n[i][j]=tot++;
	T=tot++;
	for(int j=0;j<N;j++)
	{
		int w;
		scanf("%d",&w);
		addedge(S,n[0][j],w);
	}
	for(int i=0;i<N-1;i++)
	{
		for(int j=0;j<N;j++)
		{
			int w;
			scanf("%d",&w);
			addedge(n[i][j],n[i+1][j],w);
		}
	}
	for(int j=0,w;j<N;j++)
	{
		scanf("%d",&w);
		addedge(n[N-1][j],T,w);
	}
	for(int i=0;i<N;i++)
	{
		int w;
		scanf("%d",&w);
		addedge(n[i][0],T,w);
		for(int j=1;j<N;j++)
		{
			scanf("%d",&w);
			addedge(n[i][j],n[i][j-1],w);
		}
		scanf("%d",&w);
		addedge(S,n[i][N-1],w);
	}
	for(int j=0;j<N;j++)
	{
		int w;
		scanf("%d",&w);
		addedge(n[0][j],S,w);
	}
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			int w;
			scanf("%d",&w);
			addedge(n[i][j],n[i-1][j],w);
		}
	}
	for(int j=0;j<N;j++)
	{
		int w;
		scanf("%d",&w);
		addedge(T,n[N-1][j],w);
	}
	for(int i=0;i<N;i++)
	{
		int w;
		scanf("%d",&w);
		addedge(T,n[i][0],w);
		for(int j=1;j<N;j++)
		{
			scanf("%d",&w);
			addedge(n[i][j-1],n[i][j],w);
		}
		scanf("%d",&w);
		addedge(n[i][N-1],S,w);
	}
	dijkstra();
	return 0;
}
