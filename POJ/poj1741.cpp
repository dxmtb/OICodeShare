/*
 * Problem: poj1741 Tree
 * Time: 2011.06.22
 * Author: dxmtb
 * State: Solved
 * Memo: 树的分治
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=10005;
const int oo=~0u>>2;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXN*2],*mem;

inline void addedge(int u,int v,int w)
{
	adj[u]=new (mem++)Node(v,w,adj[u]);
	adj[v]=new (mem++)Node(u,w,adj[v]);
}

bool cut[MAXN];
int N,K;

vector<pair<int,int> > vis,cvis;
int sum[MAXN],father[MAXN];
void dp(int u,int dis)
{
	vis.push_back(make_pair(dis,u));
	sum[u]=1;
	for(Node *p=adj[u];p;p=p->next)
		if (!cut[p->v] && p->v!=father[u])
		{
			father[p->v]=u;
			dp(p->v,dis+p->w);
			sum[u]+=sum[p->v];
		}
}

void rebuild(const int &u)
{
	vis=cvis;
	for(int i=0;i<(int)vis.size();i++)
		swap(vis[i].first,vis[i].second);
	int i=1;
	for(Node *p=adj[u];p;p=p->next)
		if (!cut[p->v])
		{
			assert(father[p->v]==u);
			int j=i;
			while(vis[i].first!=p->v)
				i++;
			int bv=vis[j].first;
			while(j<i)
				vis[j++].first=bv;
		}
	int bv=vis[i].first,size=vis.size();
	while(i<size)
		vis[i++].first=bv;
}

int partition(int);

int calcu(int u)
{
	cut[u]=true;
	vis.clear();
	father[u]=-1;
	dp(u,0);
	cvis=vis;
	sort(vis.begin(),vis.end());
	int size=vis.size(),ret=0;
	for(int i=0,j=size-1;i<size && i<j;i++)
	{
		while(i<j && vis[i].first+vis[j].first>K)
			j--;
		ret+=j-i;
	}
	rebuild(u);
	sort(vis.begin(),vis.end());
	for(int i=0;i<size;)
	{
		int k=i;
		while(k+1<size && vis[k+1].first==vis[i].first)
			k++;
		int j=k;
		while(i<k && i<j)
		{
			while(i<j && vis[i].second+vis[j].second>K)
				j--;
			ret-=j-i;
			i++;
		}
		i=k+1;
	}
	for(Node *p=adj[u];p;p=p->next)
		if (!cut[p->v])
			ret+=partition(p->v);
	return ret;
}

int partition(int u)
{
	vis.clear();
	father[u]=-1;
	dp(u,0);
	if (vis.size()==0)
		return 0;
	const int &tot=sum[u];
	int root=-1,mins=oo;
	for(int i=0;i<(int)vis.size();i++)
	{
		int v=vis[i].second;
		int maxs=tot-sum[v];
		for(Node *p=adj[v];p;p=p->next)
			if (!cut[p->v] && father[v]!=p->v && sum[p->v]>maxs)
				maxs=sum[p->v];
		if (maxs<mins)
			mins=maxs,root=v;
	}
	return calcu(root);
}

int main()
{
	freopen("1741.in","r",stdin);
	while(true)
	{
		scanf("%d%d",&N,&K);
		if (N==0 && K==0)
			break;
		memset(adj,0,sizeof(adj));
		memset(cut,false,sizeof(cut));
		mem=pool;
		for(int i=0;i<N-1;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addedge(u,v,w);
		}
		int re=partition(1);
		printf("%d\n",re);
	}
	return 0;
}
