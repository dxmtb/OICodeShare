/*
ID: dxmtb
PROG: 腾讯大战360
TIME: 2010.11.9
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN=5005;
const int oo=1e9;

struct Node
{
	int v,w;
	Node *next;
	Node(int a,int b,Node *d):v(a),w(b),next(d){}
}*adj[MAXN];

int N,M,S,T,re=oo;
int dis[2][MAXN];

void add(int u,int v,int w)
{
	adj[u]=new Node(v,w,adj[u]);
	adj[v]=new Node(u,w,adj[v]);
}

bool in[MAXN];
void spfa(int *dis,int s)
{
	for(int i=1;i<=N;i++)
		dis[i]=oo;
	dis[s]=0;
	queue<int> q;
	q.push(s);in[s]=true;
	while(q.size())
	{
		int u=q.front();q.pop();
		in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				if (!in[p->v])
				{
					q.push(p->v);
					in[p->v]=true;
				}
			}
	}
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	scanf("%d%d",&S,&T);
	spfa(dis[0],S);
	spfa(dis[1],T);
	for(int i=1;i<=N;i++)
		re=min(re,max(dis[0][i],dis[1][i]));
	if (re==oo) printf("Peace!\n");
	else printf("%d\n",re);
	return 0;
}
