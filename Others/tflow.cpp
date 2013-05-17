/*
ID: dxmtb
PROG: 总流量
TIME: 2010.12.26
STATE: Solved
MEMO: 最大流
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN=60;
const int oo=0x7fffffff;
const int S=0,T=25;

struct Node
{
	int v,c;
	Node *next,*back;
	Node (int a,int b,Node *n):v(a),c(b),next(n){}
}*adj[MAXN];

int maxflow,N;

void addedge(int a,int b,int c)
{
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,0,adj[b]);
	adj[a]->back=adj[b];
	adj[b]->back=adj[a];
}

int lv[MAXN];
bool dinic_lable()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	q.push(S);
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&lv[p->v]==-1)
			{
				q.push(p->v);
				lv[p->v]=lv[u]+1;
			}
		if (lv[T]!=-1)
			return true;
	}
	return lv[T]!=-1;
}

void dinic_aug()
{
	int stack[MAXN],stop=0;
	Node *path[MAXN];
	stack[stop++]=S;
	while(stop)
	{
		int u=stack[stop-1];
		if (u==T)
		{
			int delta=oo;
			for(int i=1;i<stop;i++)
				delta=min(delta,path[i]->c);
			for(int i=stop-1;i;i--)
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
				if (path[i]->c==0)
					stop=i-1;
			}
			maxflow+=delta;
		}
		else
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
					break;
			if (p)
				path[stop]=p,stack[stop++]=p->v;
			else lv[u]=-1,stop--;
		}
	}
}

void dinic()
{
	while(dinic_lable())
		dinic_aug();
}

int main()
{
	freopen("tflow.in","r",stdin);
	freopen("tflow.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		int c;
		char a,b;
		do{a=getchar();}
			while(!((a>='A'&&a<='Z')||(a>='a'&&a<='z')));
		if (a>='A'&&a<='Z') a-='A';
		else a=a-'a'+26;
		do{b=getchar();}
			while(!((b>='A'&&b<='Z')||(b>='a'&&b<='z')));
		if (b>='A'&&b<='Z') b-='A';
		else b=b-'a'+26;
		scanf("%d",&c);
		addedge(a,b,c);
	}
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
