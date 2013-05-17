/*
ID: dxmtb
PROG: 线性规划与网络流24题 太空飞行计划问题
TIME: 2010.10.8
STATE: Solved
MEMO: 最小割
*/
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=105;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int a,int b,Node *ne,Node *ba=0):v(a),c(b),next(ne),back(ba){}
}*adj[MAXN];

int m,n,s,t;

void addedge(int a,int b,int c)
{
//	printf("add %d %d %d\n",a,b,c);
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,0,adj[b],adj[a]);
	adj[a]->back=adj[b];
}

int lv[MAXN];
bool dinic_lable()
{
	memset(lv,-1,sizeof(lv));
	queue<int> q;
	q.push(s);lv[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (lv[p->v]==-1&&p->c>0)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
	}
	if (lv[t]!=-1) return true;
	return false;
}

int maxflow;
void dinic_agu()
{
	int sta[MAXN],stop=1;
	Node *path[MAXN],*p;
	sta[0]=s;
	while(stop)
	{
		int u=sta[stop-1];
		if (u==t)
		{
			int delta=oo;
			for(int i=1;i<stop;i++)
				if (path[i]->c<delta)
					delta=path[i]->c;
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
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					path[stop]=p;
					sta[stop++]=p->v;
					break;
				}
			if (!p) stop--,lv[u]=-1;
		}
	}
}

void dinic()
{
	while(dinic_lable())
		dinic_agu();
}

int sum;

bool vis[MAXN];
void dfs(int u)
{
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v]&&p->c>0)
			dfs(p->v);
}

void print()
{
	bool first=true;
	for(int i=1;i<=m;i++)
		if (vis[i])
		{
			if (first) first=false;
			else cout<<' ';
			cout<<i;
		}
	cout<<endl;
	first=true;
	for(int i=m+1;i<=m+n;i++)
		if (vis[i])
		{
			if (first) first=false;
			else cout<<' ';
			cout<<i-m;
		}
	cout<<endl;
	cout<<sum-maxflow<<endl;
}

int main()
{
	freopen("shut.in","r",stdin);
	freopen("shut.out","w",stdout);
	cin>>m>>n;
	s=0;t=m+n+1;
	for(int i=1;i<=m;i++)
	{
		string str;
		do getline(cin,str);while(str=="\n"||str==""||str=="\r");
		stringstream ss(str);
		int a;
		ss>>a;
		sum+=a;
		addedge(s,i,a);
		while(ss>>a)
			addedge(i,a+m,oo);
	}
	for(int i=m+1;i<=m+n;i++)
	{
		int a;
		cin>>a;
		addedge(i,t,a);
	}
	dinic();
	dfs(s);
	print();
	return 0;
}
