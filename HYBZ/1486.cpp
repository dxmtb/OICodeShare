/*
ID: dxmtb
PROG: [HNOI2009]最小圈
TIME: 2011.03.26
STATE: Solved
MEMO: 二分答案+判负环
*/
#include <cstdio>

const int MAXN=3005;

struct Node
{
	int v;
	double w,ow;
	Node *next;
	Node (int _v,double _w,Node *_next):
		v(_v),ow(_w),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v,double w)
{
	adj[u]=new Node(v,w,adj[u]);
}

double dis[MAXN];
bool vis[MAXN];
bool dfs(int u)
{
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (dis[u]+p->w<dis[p->v])
		{
			if (!vis[p->v])
			{
				dis[p->v]=dis[u]+p->w;
				if (dfs(p->v))
				{
					vis[u]=false;
					return true;
				}
			}
			else
			{
				vis[u]=false;
				return true;
			}
		}
	vis[u]=false;
	return false;
}

int N,M;
bool check(double m)
{
	for(int i=1;i<=N;i++)
		for(Node *p=adj[i];p;p=p->next)
			p->w=p->ow-m;
	for(int i=1;i<=N;i++)
		dis[i]=0;
	for(int i=1;i<=N;i++)
		if (dfs(i))
			return true;
	return false;
}

int main()
{
	freopen("1486.in","r",stdin);
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int i,j;
		double w;
		scanf("%d%d%lf",&i,&j,&w);
		addedge(i,j,w);
	}
	double l=-1e7,r=1e7;
	while(r-l>1e-9)
	{
		double mid=(l+r)/2;
		if (check(mid)) r=mid;
		else l=mid;
	}
	printf("%.8f\n",l);
	return 0;
}
