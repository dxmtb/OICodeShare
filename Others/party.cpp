/*
ID: dxmtb
PROG: Party
TIME: 2010.11.11
STATE: Solved
MEMO: ×î¶ÌÂ·
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=1005;
const int oo=int(1e9);

struct Node
{
	int v,w;
	Node *next;
	Node(int a,int b,Node *c):v(a),w(b),next(c){}
}*adj[MAXN];

inline void add(int u,int v,int w)
{
	adj[u]=new Node(v,w,adj[u]);
}


int n,m,x,re;

bool in[MAXN];
int dis[MAXN][MAXN];
inline void spfa(int s,int dis[])
{
	for(int i=1;i<=n;i++)
		dis[i]=oo;
	deque<int> q;
	q.push_back(s);in[s]=true;
	dis[s]=0;
	while(q.size())
	{
		int u=q.front();q.pop_front();
		in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				if (!in[p->v])
				{
					if (!q.empty()&&dis[p->v]>dis[q.front()]) q.push_back(p->v);
					else q.push_front(p->v);
					in[p->v]=true;
				}
			}
	}
}

int main()
{
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	scanf("%d%d%d",&n,&m,&x);
	for(int i=0,u,v,t;i<m;i++)
	{
		scanf("%d%d%d",&u,&v,&t);
		add(u,v,t);
	}
	for(int i=1;i<=n;i++)
		spfa(i,dis[i]);
	for(int i=1;i<=n;i++)
		if (dis[i][x]+dis[x][i]>re)
			re=dis[i][x]+dis[x][i];
	printf("%d\n",re);
	return 0;
}
