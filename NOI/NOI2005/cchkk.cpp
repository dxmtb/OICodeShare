/*
ID: dxmtb
PROG: NOI2005 聪聪与可可
TIME: 2011.02.09
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=1005;

struct Node
{
	int v;
	Node *next;
	Node(int _v,Node *_next):v(_v),next(_next){}
	Node(){}
	void *operator new(unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*3],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	adj[v]=new (mem++)Node(u,adj[v]);
}

int next[MAXN][MAXN];
double f[2][MAXN][MAXN];
inline void bfs(int s,int next[])
{
	int lv[MAXN];
	memset(lv,-1,sizeof(lv));
	queue<int> q;
	q.push(s);
	lv[s]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (lv[p->v]==-1)
			{
				q.push(p->v);
				lv[p->v]=lv[u]+1;
				next[p->v]=u;
			}
			else if (lv[p->v]==lv[u]+1&&u<next[p->v])
				next[p->v]=u;
	}
}

bool in[MAXN][MAXN];
int main()
{
	freopen("cchkk.in","r",stdin);
	freopen("cchkk.out","w",stdout);
	int N,E;
	register int C,M;
	int d[MAXN];
	memset(d,0,sizeof(d));
	scanf("%d%d",&N,&E);
	scanf("%d%d",&C,&M);
	while(E--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=N;i++)
	{
		adj[i]=new (mem++)Node(i,adj[i]);
		d[i]++;
	}
	for(int i=1;i<=N;i++)
		bfs(i,next[i]);
	f[0][M][C]=1;
	bool flag=true;
	double re=0;
	queue<pair<int,int> >q;
	q.push(make_pair(M,C));
	for(int i=0;flag;i++)
	{
		double (*g)[MAXN]=f[(i&1)],
		    (*h)[MAXN]=f[(i+1)&1];
		memset(h,false,sizeof(f[0]));
		flag=false;
		for(int j=1;j<=N;j++)
			if (g[j][j]>0)
			{
				re+=i*g[j][j];
				g[j][j]=0;
			}
		int size=q.size();
		memset(in,false,sizeof(in));
		while(size--)
		{
			M=q.front().first,C=q.front().second;
			q.pop();
			int *nxt=next[M],*dp=d+M;
			double *gp=g[M];
				if (g[M][C]>0)
				{
					flag=true;
					int nC=nxt[C];
					if (nC!=M)
						nC=nxt[nC];
					if (nC==M)
					{
						h[M][nC]+=gp[C];
						continue;
					}
					for(Node *p=adj[M];p;p=p->next)
					{
						int nM=p->v;
						h[nM][nC]+=gp[C]/(*dp);
						if (nM!=nC&&!in[nM][nC])
						{
							q.push(
							make_pair(nM,nC));
							in[nM][nC]=true;
						}
					}
				}
		}
	}
	printf("%.3lf\n",re);
	return 0;
}


