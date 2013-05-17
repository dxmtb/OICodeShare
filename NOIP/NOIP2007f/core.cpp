/*
ID: dxmtb
PROG: NOIP2007
TIME: 2010.8.26
STATE: Solved
MEMO: 搜索 （存在数组越界）
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN=400;
const int oo=0x7fffffff;

struct Node
{
	int v,w;
	Node *next;
	Node(int a,int b,Node *c):v(a),w(b),next(c){}
};

int n,s;
Node *adj[MAXN],*adj2[MAXN];
int dis[MAXN][MAXN];

int father[MAXN];
int getfather(int u)
{
	if (father[u]==u)
		return u;
	return father[u]=getfather(father[u]);
}

void unite(int a,int b)
{
	father[b]=getfather(a);
}

bool vis[MAXN],color[MAXN];
int dis2[MAXN];
int lcar[MAXN][MAXN];
int trfather[MAXN];
void lca(int u,int father)
{
	vis[u]=true;
	trfather[u]=father;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v])
		{
			dis2[p->v]=dis2[u]+p->w;
			lca(p->v,u);
			unite(u,p->v);
		}
	for(int i=0;i<n;i++)
		if (color[i])
		{
			dis[i][u]=dis[u][i]=dis2[u]+dis2[i]-2*dis2[getfather(i)];
			lcar[i][u]=lcar[u][i]=getfather(i);
		}
	color[u]=true;
}

void add(Node **adj,int a,int b,int c)
{
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,c,adj[b]);
}

int re=oo;
int maxdis=0;
int emd[MAXN];//each min dis
int mdis[MAXN];
int W[MAXN][MAXN];

void dfs(int u,int length,int father)
{
	if (length>s)return ;
	for(Node *p=adj[u];p;p=p->next)
		if (p->v!=father)
		{
			if (length+p->w>s)
			{
				int tre=0;
				for(int i=0;i<n;i++)
					if (emd[i]>tre)
						tre=emd[i];
				if (tre<re)
				{
					re=tre;
//					printf("%d\n",re);
				}
			}
			else
			{
				int cemd[MAXN];
				for(int i=0;i<n;i++)
				{
					cemd[i]=emd[i];
					if (dis[p->v][i]<emd[i])
						emd[i]=dis[p->v][i];
				}
				dfs(p->v,length+p->w,u);
				for(int i=0;i<n;i++)
					emd[i]=cemd[i];
			}
		}
}

bool temp[MAXN][MAXN];
void addnew(int a,int b)
{
	int k=lcar[a][b],s,t;
	for(t=trfather[a],s=a;s!=k;s=t,t=trfather[t])
		temp[t][s]=temp[s][t]=true;
	for(t=trfather[b],s=b;s!=k;s=t,t=trfather[t])
		temp[t][s]=temp[s][t]=true;
}

int main()
{
	freopen("core.in","r",stdin);
	freopen("core.out","w",stdout);
	scanf("%d%d",&n,&s);
	for(int i=1;i<n;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		W[a][b]=W[b][a]=c;
		a--,b--;
		add(adj,a,b,c);
	}
	for(int i=0;i<n;i++)
		father[i]=i;
	lca(0,0);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		if (i!=j&&dis[i][j]>mdis[i])
			mdis[i]=dis[i][j];
		if (mdis[i]>maxdis)
			maxdis=mdis[i];
		if (mdis[i]<re)
			re=mdis[i];
	}
//	cerr<<maxdis<<endl;
	bool flag[MAXN];
	for(int i=0;i<n;i++)
		if (mdis[i]==maxdis&&!flag[i])
		{
			memset(adj2,0,sizeof(adj2));
			memset(temp,false,sizeof(temp));
			for(int j=0;j<n;j++)
				if (dis[i][j]==maxdis)
				{
					addnew(i,j);
					flag[j]=true;
				}
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					if (temp[j][k])
					add(adj2,j,k,W[j][k]);
			for(int k=0;k<n;k++)
				if (adj2[k])
				{
					for(int j=0;j<n;j++)
						emd[j]=dis[k][j];
					dfs(k,0,k);
				}
		}
	printf("%d\n",re);
	return 0;
}

