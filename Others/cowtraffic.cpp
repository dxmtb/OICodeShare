/*
ID: dxmtb
PROG: 奶牛交通
TIME: 2010.10.14
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=50005;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
}*adj[2][MAXN];

int n,m,re;
int id[2][MAXN],d[2][MAXN];

void addedge(int a,int b)
{
	adj[0][a]=new Node(b,adj[0][a]);
	id[0][b]++;
	adj[1][b]=new Node(a,adj[1][b]);
	id[1][a]++;
}

void solve(int id[],int d[],Node *adj[])
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		if (!id[i])
		{
			q.push(i);
			d[i]=1;
		}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if (adj[u]&&d[u]>re)
			re=d[u];
		for(Node *p=adj[u];p;p=p->next)
		{
			d[p->v]+=d[u];
			id[p->v]--;
			if (!id[p->v])
				q.push(p->v);
		}
	}
}

void print()
{
	for(int i=1,t;i<=n;i++)
		for(Node *p=adj[0][i];p;p=p->next)
			if ((t=d[0][i]*d[1][p->v])>re)
				re=t;
}

int main()
{
	freopen("cowtraffic.in","r",stdin);
	freopen("cowtraffic.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
	}
	solve(id[0],d[0],adj[0]);
	solve(id[1],d[1],adj[1]);
	print();
	printf("%d\n",re);
	return 0;
}


