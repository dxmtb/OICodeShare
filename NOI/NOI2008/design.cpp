/*
 * Problem: NOI2008 设计路线
 * Time: 2011.05.25
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>
#include <queue>
using namespace std;

typedef long long s64;
const int MAXN=100005,MAXD=18;
int MO;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node (){}
}*adj[MAXN],pool[MAXN*2],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	adj[v]=new (mem++)Node(u,adj[v]);
}

vector<int> son[MAXN];
int N;

bool bfs()
{
	bool vis[MAXN];
	for(int i=2;i<=N;i++)
		vis[i]=false;
	queue<int> q;
	q.push(1);
	vis[1]=true;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (!vis[p->v])
			{
				vis[p->v]=true;
				son[u].push_back(p->v);
				q.push(p->v);
			}
	}
	for(int i=1;i<=N;i++)
		if (!vis[i])
			return false;
	return true;
}

int d[MAXN][2],g[2],re;
void dp(int u)
{
	int size=son[u].size();
	if (size==0)
	{
		d[u][0]=d[u][1]=0;
		return ;
	}
	for(int i=0;i<size;i++)
		dp(son[u][i]);
	g[0]=0;g[1]=10000000;
	for(int i=0;i<size;i++)
	{
		int v=son[u][i];
		d[u][1]=min(max(g[0],d[v][0]+1),min(max(g[1],d[v][0]+1),max(g[0],d[v][1])));
		d[u][0]=min(d[u][1],max(g[1],d[v][1]));
		g[1]=min(max(g[0],d[v][1]),max(g[1],d[v][0]+1));
		g[0]=max(g[0],d[v][0]+1);
	}
}

s64 f[MAXN][MAXD][2];
s64 mulf[MAXN],mulb[MAXN];
void cal(int u)
{
	int size=son[u].size();
	if (size==0)
	{
		for(int i=0;i<=re;i++)
			f[u][i][0]=f[u][i][1]=1;
		return ;
	}
	for(int i=0;i<size;i++)
		cal(son[u][i]);
	for(int j=1;j<=re;j++)
	{
		s64 &ans=f[u][j][0];
		ans=1;
		for(int i=0;i<size;i++)
			ans=ans*f[son[u][i]][j-1][0]%MO;
	}
	if (size==1)
		f[u][0][0]=(f[u][0][0]+f[son[u][0]][0][1])%MO;
	for(int j=1;j<=re;j++)
	{
		for(int i=0;i<size;i++)
		{
			mulf[i]=f[son[u][i]][j-1][0];
			if (i-1>=0)
				mulf[i]=mulf[i]*mulf[i-1]%MO;
		}
		for(int i=size-1;i>=0;i--)
		{
			mulb[i]=f[son[u][i]][j-1][0];
			if (i+1<size)
				mulb[i]=mulb[i]*mulb[i+1]%MO;
		}
		for(int i=0;i<size;i++)
		{
			int m1,m2;
			if (i-1>=0)
				m1=mulf[i-1];
			else
				m1=1;
			if (i+1<size)
				m2=mulb[i+1];
			else
				m2=1;
			f[u][j][0]=(f[u][j][0]+m1*f[son[u][i]][j][1]%MO*m2)%MO;
		}
	}
	for(int j=0;j<=re;j++)
		f[u][j][1]=f[u][j][0];
	if (size==2)
		f[u][0][0]=(f[u][0][0]+f[son[u][0]][0][1]*f[son[u][1]][0][1])%MO;
	for(int j=1;j<=re;j++)
	{
		for(int i=0;i<size;i++)
		{
			mulf[i]=f[son[u][i]][j-1][0];
			if (i-1>=0)
				mulf[i]=mulf[i]*mulf[i-1]%MO;
		}
		for(int i=size-1;i>=0;i--)
		{
			mulb[i]=f[son[u][i]][j-1][0];
			if (i+1<size)
				mulb[i]=mulb[i]*mulb[i+1]%MO;
		}
		s64 s=f[son[u][0]][j][1];
		for(int i=1;i<size;i++)
		{
			int m2;
			if (i+1<size)
				m2=mulb[i+1];
			else
				m2=1;
			f[u][j][0]=(f[u][j][0]+s*f[son[u][i]][j][1]%MO*m2)%MO;
			s=(s*f[son[u][i]][j-1][0]+f[son[u][i]][j][1]*mulf[i-1])%MO;
		}
	}
}

int M;
int main()
{
	freopen("design.in","r",stdin);
	freopen("design.out","w",stdout);
	scanf("%d%d%d",&N,&M,&MO);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	if (M<N-1 || !bfs())
		printf("-1\n-1\n");
	else
	{
		dp(1);
		re=d[1][0];
		printf("%d\n",re);
		cal(1);
		printf("%lld\n",f[1][re][0]);
	}
	return 0;
}
