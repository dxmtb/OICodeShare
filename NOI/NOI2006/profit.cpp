/*
ID: dxmtb
PROG: NOI2006 最大获利
TIME: 2010.9.11
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=60000;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int a,int b,Node *e,Node* d=0):v(a),c(b),next(e),back(d){}
}*adj[MAXN];

int s,t;
int n,m;
int total;

void addedge(int a,int b,int c)
{
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,0,adj[b],adj[a]);
	adj[a]->back=adj[b];
}

int lv[MAXN];
queue<int> q;
bool dinic_label()
{
	for(int i=s;i<=t;i++)
		lv[i]=oo;
	while(!q.empty())q.pop();
	lv[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&lv[p->v]==oo)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[t]!=oo) 
			return true;
	}
//	if (lv[t]!=oo) return true;
	return false;
}

int maxflow;
int stack[MAXN],stop;
Node *edge[MAXN],*p;
void dinic_agu()
{
	stack[0]=s;stop=1;
	while(stop)
	{
		int u=stack[stop-1];
		if (u==t)
		{
			int delta=oo;
			for(int i=1;i<stop;i++)
				if (edge[i]->c<delta)
					delta=edge[i]->c;
			for(int i=stop-1;i;i--)
			{
				edge[i]->c-=delta;
				edge[i]->back->c+=delta;
				if (!edge[i]->c)
					stop=i;
			}
			maxflow+=delta;
		}
		else
		{
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					edge[stop]=p;
					stack[stop++]=p->v;
					break;
				}
			if (!p)
				stop--,lv[u]=-1;
		}
	}
}

void dinic()
{
	while(dinic_label())
		dinic_agu();
}
	
int main()
{
	freopen("profit.in","r",stdin);
	freopen("profit.out","w",stdout);
	scanf("%d%d",&n,&m);
	s=0;t=n+m+1;
	for(int i=1;i<=n;i++)
	{
		int temp;
		scanf("%d",&temp);
		addedge(s,i,temp);
	}
	for(int i=n+1;i<=n+m;i++)
	{
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		addedge(t1,i,oo);
		addedge(t2,i,oo);
		addedge(i,t,t3);
		total+=t3;
	}
	dinic();
	printf("%d\n",total-maxflow);
	return 0;
}
