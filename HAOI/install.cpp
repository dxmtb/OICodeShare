/*
ID: dxmtb
PROG: HAOI2010 软件安装
TIME: 2011.03.17
STATE: Solved
MEMO: 有依赖背包 判环 树形dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=205,MAXM=505;

struct Node
{
	int v;
	Node *next;
	Node(int _v,Node *_next):v(_v),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v)
{
	adj[u]=new Node(v,adj[u]);
}

int N,M,W[MAXN],V[MAXN],D[MAXN];
bool vis[MAXN],in[MAXN];
int father[MAXN],circle[MAXN];
int P;
void dfs(int u)
{
	in[u]=true;
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v])
		{
			father[p->v]=u;
			dfs(p->v);
		}
		else
		{
			if (in[p->v])
			{
				int v=u;
				P++;
				while(true)
				{
					V[P]+=V[v];
					W[P]+=W[v];
					circle[v]=P;
					if (v==p->v) break;
					v=father[v];
				}
				v=u;
				while(true)
				{
					for(Node *p2=adj[v];p2;p2=p2->next)
						if (!circle[p2->v])
							addedge(P,p2->v);
					if (v==p->v) break;
					v=father[v];
				}
			}
			else
				father[p->v]=u;			
		}
	in[u]=false;
}

int f[MAXN][MAXM],d[MAXM];
void dp(int u)
{
	vis[u]=true;
	memcpy(f[u],d,sizeof(d));
	for(int i=M;i>=V[u];i--)
		f[u][i]=max(f[u][i],f[u][i-V[u]]+W[u]);
	for(Node *p=adj[u];p;p=p->next)
		dp(p->v);
	for(int i=M;i>=V[u];i--)
		d[i]=d[i-V[u]]+W[u];
	for(int i=V[u]-1;i>=0;i--)
		d[i]=0;
	for(int i=M;i>=0;i--)
		d[i]=max(d[i],f[u][i]);
}

int main()
{
	freopen("install.in","r",stdin);
	freopen("install.out","w",stdout);
	scanf("%d%d",&N,&M);
	P=N;
	for(int i=1;i<=N;i++)
		scanf("%d",V+i);
	for(int i=1;i<=N;i++)
		scanf("%d",W+i);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",D+i);
		if (D[i]!=0)
			addedge(D[i],i);
	}
	for(int i=1;i<=N;i++)
		if (!vis[i])
			dfs(i);
	memset(vis,false,sizeof(vis));
	for(int i=N+1;i<=P;i++)
		dp(i);
	for(int i=1;i<=N;i++)
		if (!vis[i] && !circle[i] && father[i]==0)
			dp(i);
	printf("%d\n",d[M]);
	return 0;
}
