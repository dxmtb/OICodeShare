/*
ID: dxmtb
PROG: 线性规划与网络流24题 最长k可重区间集问题
TIME: 2011.02.12
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;

const int MAXN=1000;
const int oo=0x7fffffff;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,int _w,Node *_next,Node *_back=NULL):
		v(_v),c(_c),w(_w),next(_next),back(_back){}
}*adj[MAXN],pool[MAXN*5],*mem=pool;

inline void addedge(int u,int v,int c,int w)
{
	adj[u]=new Node(v,c,w,adj[u]);
	adj[v]=new Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T,mincost,piS;
bool label()
{
	deque<int> q;
	int dis[MAXN];
	for(int i=S;i<=T;i++)
		dis[i]=oo;
	dis[T]=0;
	q.push_back(T);
	while(q.size())
	{
		int u=q.front();q.pop_front();
		int dt;
		for(Node *p=adj[u];p;p=p->next)
			if (p->back->c && dis[p->v]>(dt=dis[u]-p->w))
			{
				dis[p->v]=dt;
				if (q.empty()||dt>dis[q.front()])
					q.push_back(p->v);
				else q.push_front(p->v);
			}
	}
	for(int u=S;u<=T;u++)
		for(Node *p=adj[u];p;p=p->next)
			p->w+=dis[p->v]-dis[u];
	piS+=dis[S];
	return dis[S]<oo;
}

bool v[MAXN];
int augment(int u,int m)
{
	if (u==T) return mincost+=piS*m,m;
	int l=m;
	for(Node *p=adj[u];p;p=p->next)
		if (!v[p->v] && !p->w &&p->c)
		{
			v[p->v]=true;
			int d=augment(p->v,min(l,p->v));
			l-=d;
			p->c-=d,p->back->c+=d;
			if (!l)
				return m;
		}
	return m-l;
}

void solve()
{
	while(label())
		do memset(v,false,sizeof(v));
		while(augment(S,oo));
}

pair<int,int> line[MAXN];
int w[MAXN];
int main()
{
	freopen("interv.in","r",stdin);
	freopen("interv.out","w",stdout);
	int N,K;
	vector<pair<int,int> > v;
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&line[i].first,&line[i].second);
		w[i]=line[i].first-line[i].second;
		v.push_back(make_pair(line[i].first,i*2-1));
		v.push_back(make_pair(line[i].second,i*2));
	}
	sort(v.begin(),v.end());
	S=0,T=0;
	for(int i=0;i<v.size();i++)
	{
		if (i==0||v[i].first!=v[i-1].first) T++;
		if (v[i].second&1) line[(v[i].second+1)/2].first=T;
		else line[v[i].second/2].second=T;
	}	
	T++;
	addedge(S,1,K,0);
	for(int i=1;i<T;i++)
		addedge(i,i+1,oo,0);
	for(int i=1;i<=N;i++)
		addedge(line[i].first,line[i].second,1,w[i]);
	solve();
	printf("%d\n",-mincost);
	return 0;
}
