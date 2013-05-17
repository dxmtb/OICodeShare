/*
ID: dxmtb1
PROG: milk6
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN=32,MAXM=1000;
typedef long long s64;
const s64 oo=~0ull>>1;

struct Node
{
	int v;
	s64 c;
	Node *next,*back;
	Node(int _v,s64 _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
	Node(){}
	void *operator new (unsigned,void *p){return p;}
}*adj[MAXN],*last[MAXN],pool[MAXM*2],*mem=pool;

inline void addedge(int u,int v,s64 c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXM];
bool label()
{
	queue<int> q;
	q.push(S);
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		last[u]=adj[u];
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0 && lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[T]!=-1)
			return true;
	}
	return false;
}

int delta;
s64 maxflow;
void augment()
{
	Node *path[MAXN];
	int sta[MAXN]={S},size=1;
	while(size)
	{
		int u=sta[size-1];
		if (u!=T)
		{
			for(Node *&p=last[u];p;p=p->next)
				if (p->c>0 && lv[p->v]==lv[u]+1)
				{
					path[size]=p,
					sta[size++]=p->v;
					break;
				}
			if (!last[u])
				lv[u]=-1,size--;
		}
		else
		{
			s64 delta=oo;
			int j;
			for(int i=size-1;i;i--)
				if (path[i]->c<delta)
				{
					delta=path[i]->c;
					j=i;
				}
			for(int i=size-1;i;i--)
				path[i]->c-=delta,
				path[i]->back->c+=delta;
			size=j;
			maxflow+=delta;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

int N,M;
int main()
{
	freopen("milk6.in","r",stdin);
	freopen("milk6.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		u--,v--;
		addedge(u,v,((s64)c*1001+1)*499501+i);
	}
	S=0,T=N-1;
	dinic();
	printf("%lld %lld\n",maxflow/499501/1001,maxflow/499501%1001);
	label();
	vector<int> v;
	for(int i=S;i<=T;i++)
		if (lv[i]!=-1)
			for(Node *p=adj[i];p;p=p->next)
				if ((p-pool)%2==0 && lv[p->v]==-1)
					v.push_back(p->back->c%499501);
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
		printf("%d\n",v[i]+1);
	return 0;
}
