/*
 * Problem: [ZJOI2006]物流运输trans
 * Time: 2011.04.19
 * Author: dxmtb
 * State: Solved
 * Memo: dp+最短路
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN=105;
const int oo=~0u>>3;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v,int w)
{
	adj[u]=new Node(v,w,adj[u]);
	adj[v]=new Node(u,w,adj[v]);
}

int d[MAXN];
int N,M,K,E;
bool forbid[MAXN];

int dis[MAXN];
int spfa()
{
	queue<int> q;
	for(int i=0;i<M;i++)
		dis[i]=oo;
	dis[0]=0;
	q.push(0);
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (!forbid[p->v] && dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				q.push(p->v);
			}
	}
	return dis[M-1];
}

int unable[MAXN];
int main()
{
	freopen("1003.in","r",stdin);
	scanf("%d%d%d%d",&N,&M,&K,&E);
	while(E--)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u--,v--;
		addedge(u,v,w);
	}
	scanf("%d",&E);
	while(E--)
	{
		int u,s,t;
		scanf("%d%d%d",&u,&s,&t);
		u--;
		for(int i=s;i<=t;i++)
			unable[i]|=(1<<u);
	}
	for(int i=1;i<=N;i++)
	{
		d[i]=oo;
		memset(forbid,false,sizeof(forbid));
		for(int j=i-1;j>=0;j--)
		{
			for(int k=0;k<M;k++)
				if (unable[j+1]&(1<<k))
					forbid[k]=true;
			int t=spfa();
			if (t!=oo && d[j]+t*(i-j)+K<d[i])
				d[i]=d[j]+t*(i-j)+K;
		}
	}
	printf("%d\n",d[N]-K);
	return 0;
}
