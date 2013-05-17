/*
PROG: butter
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=1500,MAXINT=0x7fffffff;

struct Edge
{
	int v,w;
	Edge *next;
	Edge(int a=0,int b=0,Edge *n=0):v(a),w(b),next(n){}
}*adj[MAXN];

int n;
int w[MAXN][MAXN],cow[MAXN];
int dis[MAXN];

void spfa(int u)
{
	for(int i=0;i<MAXN;i++)
		dis[i]=MAXINT;
	queue<int> q;
	bool in[MAXN];
	memset(in,false,sizeof(in));
	q.push(u);
	in[u]=true;
	dis[u]=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		in[now]=false;
		for(Edge *p=adj[now];p;p=p->next)
			if(dis[now]+p->w<dis[p->v])
			{
				dis[p->v]=dis[now]+p->w;
				if(!in[p->v])
					q.push(p->v),in[p->v]=true;
			}
	}
}

int main()
{
	freopen("butter.in","r",stdin);
	freopen("butter.out","w",stdout);
	int m,p;
	scanf("%d%d%d",&n,&p,&m);
	for(int i=0;i<n;i++)
		scanf("%d",cow+i);
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		adj[a]=new Edge(b,c,adj[a]);
		adj[b]=new Edge(a,c,adj[b]);
	}
	int re=MAXINT;
	for(int i=0;i<MAXN;i++)
	{
		int t=0;
		spfa(i);
		for(int j=0;j<n;j++)
			if(dis[cow[j]]==MAXINT)
			{t=MAXINT;break;}
			else t+=dis[cow[j]];
		if (t<re)
			re=t;
	}
	printf("%d\n",re);
	return 0;
}
