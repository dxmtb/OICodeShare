/*
ID: dxmtb
PROG: NOI2003 数据生成器
TIME: 2011.03.01
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN=200005;

typedef long long s64;

struct Node
{
	int v;
	s64 w;
	Node *next;
	Node (int _v,s64 _w,Node *_next):
		v(_v),w(_w),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v,s64 w)
{
	adj[u]=new Node(v,w,adj[u]);
	adj[v]=new Node(u,w,adj[v]);
}

int N;
int father[MAXN],tot[MAXN];
s64 fatherson[MAXN];

void bfs()
{
	queue<int> q;
	bool vis[MAXN];
	memset(vis,false,sizeof(vis));
	q.push(1);vis[1]=true;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (!vis[p->v])
			{
				vis[p->v]=true;
				q.push(p->v);
				father[p->v]=u;
				fatherson[p->v]=p->w;
				tot[u]++;
			}
	}
}

s64 d1[MAXN][3];
s64 d2[MAXN];

void dp1(int u)
{
	if (tot[u]==0) {d1[u][0]=0;return;}
	for(Node *p=adj[u];p;p=p->next)
		if (p->v!=father[u])
		{
			dp1(p->v);
			for(int i=0;i<3;i++)
				if (d1[u][i]<d1[p->v][0]+p->w)
				{
					for(int k=2;k>i;k--)
						d1[u][k]=d1[u][k-1];
					d1[u][i]=d1[p->v][0]+p->w;
					break;
				}
		}
}

void dp2()
{
	queue<int> q;
	q.push(1);
	while(q.size())
	{
		int u=q.front();q.pop();
		s64 tmp;
		if (u!=1)
		{
			d2[u]=fatherson[u];
			if (d1[father[u]][0]==d1[u][0]+fatherson[u])
			{
				tmp=d1[father[u]][1]+fatherson[u];
				if (tmp>d2[u])
					d2[u]=tmp;
			}
			tmp=d2[father[u]]+fatherson[u];
			if (tmp>d2[u])
				d2[u]=tmp;
		}
		for(Node *p=adj[u];p;p=p->next)
			if (p->v!=father[u])
				q.push(p->v);
	}
}

inline s64 getre(s64 a,s64 b,s64 c)
{
	if (a<0) a=0;
	if (b<0) b=0;
	if (c<0) c=0;
	return a+b*2+c;
}

void solve()
{
	s64 re=getre(d1[1][0],d1[1][1],d1[1][2]);
	s64 tmp[3];
	for(int i=2;i<=N;i++)
	{
		for(int j=0;j<3;j++)
			tmp[j]=d1[i][j];
		for(int j=0;j<3;j++)
			if (d2[i]>tmp[j])
			{
				for(int k=2;k>j;k--)
					tmp[k]=tmp[k-1];
				tmp[j]=d2[i];
				break;
			}
		s64 nre=getre(tmp[0],tmp[1],tmp[2]);
		if (nre>re)
			re=nre;
	}
	printf("%lld\n",re);	
}

int main()
{
	freopen("jerrygen.in","r",stdin);
	freopen("jerrygen.out","w",stdout);
	int M;
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int u,v,t;
		scanf("%d%d%d",&u,&v,&t);
		addedge(u,v,t);
	}
	bfs();	
	memset(d1,128,sizeof(d1));
//	memset(d2,128,sizeof(d2));
	dp1(1);	
	dp2();
	solve();
	return 0;
}
