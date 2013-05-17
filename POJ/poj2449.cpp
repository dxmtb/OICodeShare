/*
 * Problem: poj2449 Remmarguts' Date
 * Time: 2011.06.28
 * Author: dxmtb
 * State: Solved
 * Memo: A* K短路
*/
#include <cstdio>
#include <queue>
using namespace std;

#define pb push_back
#define mp make_pair
typedef pair<int,int> Pair;
const int MAXN=1005,MAXM=100005;
const int oo=~0u>>2;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):
		v(_v),w(_w),next(_next){}
	Node (){}
	void *operator new (size_t ,void *p){return p;}
}*adj[MAXN],*adj2[MAXN],pool[MAXM*2],*mem=pool;

inline void addedge(const int &u,const int &v,const int &w)
{
	adj[u]=new (mem++)Node(v,w,adj[u]);
	adj2[v]=new (mem++)Node(u,w,adj2[v]);
}

int N,S,T,K;
int dis[MAXN];
bool sure[MAXN];
void dijktra()
{
	for(int i=1;i<=N;i++)
		dis[i]=oo;
	dis[T]=0;
	for(int i=0;i<N-1;i++)
	{
		int u=-1;
		for(int j=1;j<=N;j++)
			if (!sure[j] && (u==-1 || dis[j]<dis[u]))
				u=j;
		if (u==-1 || dis[u]==oo)
			break;
		sure[u]=true;
		for(Node *p=adj2[u];p;p=p->next)
			if (!sure[p->v] && dis[p->v]>dis[u]+p->w)
				dis[p->v]=dis[u]+p->w;
	}
}

int cnt[MAXN];
void astar()
{
	priority_queue<Pair,vector<Pair>,greater<Pair> > q;
	q.push(mp(0+dis[S],S));
	while(q.size())
	{
		int u=q.top().second,now=q.top().first;
		q.pop();
		cnt[u]++;
		if (u==T && cnt[u]==K)
		{
			printf("%d\n",now);
			return ;
		}
		if (cnt[u]<=K)
			for(Node *p=adj[u];p;p=p->next)
				if (cnt[p->v]<=K)
					q.push(mp(now-dis[u]+p->w+dis[p->v],p->v));
	}
	printf("-1\n");
}

int main()
{
//	freopen("2449.in","r",stdin);
	int M;
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	scanf("%d%d%d",&S,&T,&K);
	if (S==T)
		K++;
	dijktra();
	astar();
	return 0;
}
