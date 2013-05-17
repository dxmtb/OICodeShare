/*
 * Problem: APIO2011 方格染色
 * Time: 2011.06.02
 * Author: dxmtb
 * State: Solved
 * Memo: 映射到第一行+spfa
*/
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN=100005;
const int MO=1000000000;

struct Node
{
	int v,w;
	Node *next;
	Node (int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
}*adj[MAXN];

inline void addedge(int u,int v,int w)
{
	adj[u]=new Node (v,w,adj[u]);
	adj[v]=new Node (u,w,adj[v]);
}

int color[MAXN],father[MAXN],edge[MAXN];

inline void noans()
{
	printf("0\n");
	exit(0);
}

void join(int k,int x,int y)
{
	addedge(x,y,k);
}

bool vis[MAXN];
int before[MAXN];
void bfs(int s)
{
	queue<int> q;
	q.push(s);
	vis[s]=true;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (!vis[p->v])
			{
				if (color[p->v]==-1)
					color[p->v]=(color[u]^p->w);
				else if (color[p->v]!=(color[u]^p->w))
						noans();
				before[p->v]=u;
				vis[p->v]=true;
				q.push(p->v);
			}
			else
			{
				if (color[p->v]!=(color[u]^p->w))
					noans();
			}
	}
}

int N,M,K;
vector<pair<int,int> > v[MAXN];
bool used[MAXN];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=M;i++)
	{
		color[i]=-1;
		father[i]=i;
		edge[i]=0;
	}
	for(int i=0;i<K;i++)
	{
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		if (x==1)
			color[y]=c;
		else
		{
			v[x].push_back(make_pair(y,c));
		}
	}
	for(int i=2;i<=N;i++)
	{
		sort(v[i].begin(),v[i].end());
		int size=v[i].size();
		for(int j=1;j<size;j++)
		{
			int k1=v[i][j].first-v[i][j-1].first,k2=i-1;
			int k;
			if ((k1&1)==0 || (k2&1)==0)
				k=0;
			else
				k=1;
			k^=(v[i][j-1].second^v[i][j].second);
			join(k,v[i][j-1].first,v[i][j].first);
		}
	}
	int ans=0;
	for(int i=1;i<=M;i++)
		if (color[i]!=-1 && !vis[i])
			bfs(i);
	for(int i=1;i<=M;i++)
		if (color[i]==-1)
		{
			color[i]=0;
			bfs(i);
			ans++;
		}
	for(int i=1;i<=M;i++)
		for(Node *p=adj[i];p;p=p->next)
			if (color[i]!=(color[p->v]^p->w))
				noans();
	for(int i=2;i<=N;i++)
		if (v[i].size()==0)
			ans++;
	int re=1;
	for(int i=1;i<=ans;i++)
		re=re*2%MO;
	printf("%d\n",re);
	return 0;
}
