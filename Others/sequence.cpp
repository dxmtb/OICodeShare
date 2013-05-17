/*
 * Problem: 01串
 * Time: 2011.06.03
 * Author: dxmtb
 * State: Solved
 * Memo: 差分约束
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=1005;
const int oo=0x7fffffff;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v,int w)
{
	adj[u]=new Node(v,w,adj[u]);
}

int N;
int dis[MAXN];
bool in[MAXN];
int tot[MAXN];
inline bool spfa()
{
	queue<int> q;
	for(int i=0;i<=N;i++)
		dis[i]=oo;
	dis[N+1]=0;
	q.push(N+1);
	in[N+1]=true;
	tot[N+1]=1;
	while(q.size())
	{
		int u=q.front();q.pop();in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				if (!in[p->v])
				{
					tot[p->v]++;
					q.push(p->v);
					if (tot[p->v]>=N)
						return false;
				}
			}
	}
	return true;
}

int A0,B0,L0,A1,B1,L1;
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d%d%d%d%d%d",&N,&A0,&B0,&L0,&A1,&B1,&L1);
	for(int i=0,j=L0;j<=N;i++,j++)
	{
		addedge(i,j,L0-A0);
		addedge(j,i,B0-L0);
	}
	for(int i=0,j=L1;j<=N;i++,j++)
	{
		addedge(i,j,B1);
		addedge(j,i,-A1);
	}
	for(int i=0;i<N;i++)
	{
		addedge(i,i+1,1);
		addedge(i+1,i,0);
	}
	for(int i=0;i<=N;i++)
		addedge(N+1,i,0);
	if (spfa())
	{
		for(int i=1;i<=N;i++)
			printf("%d",dis[i]-dis[i-1]);
	}
	else
		printf("-1");
	printf("\n");
	return 0;
}
