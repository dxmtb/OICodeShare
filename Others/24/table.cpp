/*
ID: dxmtb
PROG: 线性规划与网络流24题 圆桌问题
TIME: 2011.02.02
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN=500;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int a,int b,Node *m,Node *n=NULL):v(a),c(b),next(m),back(n){}
}*adj[MAXN];

inline void addedge(int u,int v,int c)
{
	adj[u]=new Node(v,c,adj[u]);
	adj[v]=new Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXN];
bool label()
{
	queue<int>q;
	q.push(S);
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		for(Node *p=adj[u];p;p=p->next)
			if (p->c>0&&lv[p->v]==-1)
			{
				lv[p->v]=lv[u]+1;
				q.push(p->v);
			}
		if (lv[T]!=-1)
			return true;
	}
	return false;
}

int maxflow;
void augment()
{
	int stack[MAXN]={S},size=1;
	Node *path[MAXN];
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			Node *p;
			for(p=adj[u];p;p=p->next)
				if (p->c>0&&lv[p->v]==lv[u]+1)
				{
					stack[size]=p->v;
					path[size++]=p;
					break;
				}
			if (!p)
				size--,lv[u]=-1;
		}
		else
		{
			int delta=oo;
			for(int i=size-1;i;i--)
			       if (path[i]->c<delta)	       
				       delta=path[i]->c;
			for(int i=size-1;i;i--)
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
				if (path[i]->c==0)
					size=i;
			}
			maxflow+=delta;
		}
	}
}

void dinic()
{
	while(label())
		augment();
}

int m,n,sum;

void print()
{
	if (maxflow<sum)
		printf("0\n");
	else
	{
		printf("1\n");
		vector<int> ans;
		for(int i=1;i<=m;i++)
		{
			ans.clear();
			for(Node *p=adj[i];p;p=p->next)
				if (p->v>m&&p->c==0)
					ans.push_back(p->v-m);
			sort(ans.begin(),ans.end());
			printf("%d",ans[0]);
			for(int i=1;i<ans.size();i++)
				printf(" %d",ans[i]);
			printf("\n");
		}
	}
}

int main()
{
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);
	scanf("%d%d",&m,&n);
	S=0,T=m+n+1;
	for(int i=1;i<=m;i++)
	{
		int a;
		scanf("%d",&a);
		sum+=a;
		addedge(S,i,a);
	}
	for(int i=m+1;i<=m+n;i++)
	{
		int a;
		scanf("%d",&a);
		addedge(i,T,a);
	}
	for(int i=1;i<=m;i++)
		for(int j=m+1;j<=m+n;j++)
			addedge(i,j,1);
	dinic();
	print();
	return 0;
}
