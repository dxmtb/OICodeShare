/*
ID: dxmtb
PROG: 关键子工程
TIME: 2010.11.1
STATE: Solved
MEMO: 拓扑排序
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAXN=200;

struct Node
{
	int v;
	Node *next;
	Node(int a,Node *b):v(a),next(b){}
};

int n;
int t[MAXN];
Node *adj[MAXN];
vector<int> re;

void add(int a,int b)
{
	adj[a]=new Node(b,adj[a]);
}

bool vis[MAXN];
int d1[MAXN];
bool in[MAXN];
void dp1(int u,int father)
{
	d1[u]=0;
	in[u]=true;
	for(Node *p=adj[u];p;p=p->next)
	{
		if (in[p->v]&&p->v!=father)
		{
			printf("-1\n");
			exit(0);
		}
		if (d1[p->v]==0) dp1(p->v,u);
		if (d1[p->v]>d1[u])
			d1[u]=d1[p->v];
	}
	d1[u]+=t[u];
	in[u]=false;
}

void dp2(int u)
{
	vis[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!vis[p->v])
		{
			if (d1[p->v]+t[u]==d1[u])
			{
				re.push_back(p->v);
				dp2(p->v);
			}
		}
}

int main()
{
	freopen("project.in","r",stdin);
	freopen("project.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",t+i);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (i!=j)
			{
				int temp;
				scanf("%d",&temp);
				if (temp)
					add(i,j);
			}
	for(int i=0;i<n;i++)
		add(n,i);
	dp1(n,-1);
	printf("%d\n",d1[n]);
	memset(vis,false,sizeof(vis));
	dp2(n);
	bool out=false;
	vector<int>::iterator it;
	sort(re.begin(),re.end());
	int former=-1;
	for(it=re.begin();it!=re.end();it++)
		if (it==re.begin()||*it!=former)
		{
			if (out) printf(" ");
			else out=true;
			former=*it;
			printf("%d",*it+1);
		}
	return 0;
}
