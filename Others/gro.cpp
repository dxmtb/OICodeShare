/*
ID: dxmtb
PROG: 洞穴探险
TIME: 2010.9.15
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN=205;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int a,int cc,Node *b,Node *d=0):v(a),c(cc),next(b),back(d){}
}*adj[MAXN];

int s,t,n;
int maxflow;
void add(int a,int b)
{
	int c=0x7fffffff;
	if (a==s||b==t)c=1;
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,0,adj[b],adj[a]);
	adj[a]->back=adj[b];
}

int lv[MAXN];
bool label()
{
	queue<int> q;
	for(int i=0;i<n;i++)
		lv[i]=-1;
	lv[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c&&lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[t]!=-1)
			return true;
	}
	if (lv[t]!=-1)return true;
	else return false;
}

int sta[MAXN],stop;
Node *path[MAXN];
void agu()
{
	sta[0]=s;
	stop=1;
	while(stop)
	{
		int u=sta[stop-1];
		if (u==t)
		{
			int delta=0x7fffffff;
			for(int p=stop-1;p;p--)
				delta=min(delta,path[p]->c);
			for(int p=stop-1;p;p--)
			{
				path[p]->c-=delta;
				path[p]->back->c+=delta;
				if (path[p]->c==0)
					stop=p;
			}
			maxflow+=delta;
		}
		else 
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					path[stop]=p;
					sta[stop++]=p->v;
					break;
				}
			if (!p)
				stop--,lv[u]=-1;
		}
	}
}

void dinic()
{
	while(label())
		agu();
}

int main()
{
	freopen("gro.in","r",stdin);
	freopen("gro.out","w",stdout);
	scanf("%d",&n);
	s=0;t=n-1;
	for(int i=0,m;i<n-1;i++)
	{
		scanf("%d",&m);
		for(int j=0,b;j<m;j++)
		{
			scanf("%d",&b);
			b--;
			int t1=min(i,b);
			int t2=max(i,b);
			add(t1,t2);
		}
	}
	dinic();
	printf("%d\n",maxflow);
	return 0;
}


