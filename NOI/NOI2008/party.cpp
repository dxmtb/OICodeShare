/*
ID: dxmtb
PROG: NOI2008 假面舞会
TIME: 2011.03.05
STATE: Solved
MEMO: dfs
*/
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=100005;
const int oo=~0u>>1;

struct Node
{
	int v,w;
	Node *next;
	Node(const int &_v,const int &_w,Node *_next):
	    v(_v),w(_w),next(_next){}
	Node(){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN*30],*mem=pool;

void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,1,adj[u]);
	adj[v]=new (mem++)Node(u,-1,adj[v]);
}

void noanswer()
{
	printf("-1 -1\n");
	exit(0);
}

int gcd(int a,int b)
{
	int t;
	while(b!=0)
	{
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

int N,M;
int dep[MAXN];

int T;
int circle;
int d[MAXN],f[MAXN];
int mindep,maxdep;
void dfs(int u)
{
	if (d[u]!=0)
		printf("wrong\n");
	d[u]=++T;
	if (dep[u]<mindep)
		mindep=dep[u];
	if (dep[u]>maxdep)
		maxdep=dep[u];
	for(Node *p=adj[u];p;p=p->next)
		if (!d[p->v])
		{
			dep[p->v]=dep[u]+p->w;
			dfs(p->v);
		}
		else if (dep[p->v]!=dep[u]+p->w)
		{
			//find a circle
			int size=abs(dep[u]+p->w-dep[p->v]);
			circle=gcd(size,circle);
			if (circle<3)
			       	noanswer();
		}
	f[u]=++T;
}

int rmax;
void solve()
{
	for(int i=1;i<=N;i++)
		if (!f[i])
		{
			mindep=oo,maxdep=-oo;
			dfs(i);
			rmax+=maxdep-mindep+1;
		}
	if (circle)
	{
		printf("%d",circle);
		for(int i=3;i<=circle;i++)
			if (circle%i==0)
			{
				printf(" %d\n",i);
				return ;
			}
	}
	if (rmax<3) noanswer();
	else printf("%d %d\n",rmax,3);
}

int main()
{
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	solve();
	return 0;
}
