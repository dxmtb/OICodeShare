/*
ID: dxmtb
PROG: 最佳地点
TIME: 2010.12.26
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN=505;
const int oo=0x7fffffff;

struct Node
{
	int v,w;
	Node *next;
	Node (int a,int b,Node *c):v(a),w(b),next(c){}
}*adj[MAXN];

void addedge(int a,int b,int c)
{
	adj[a]=new Node(b,c,adj[a]);
	adj[b]=new Node(a,c,adj[b]);
}

int P,C,F,re=oo;
int f[MAXN];

bool in[MAXN];
int dis[MAXN];
void spfa(int S)
{
	deque<int> q;
	q.push_back(S);in[S]=true;
	for(int i=1;i<=P;i++)
		dis[i]=oo;
	dis[S]=0;
	while(q.size())
	{
		int u=q.front();q.pop_front();
		in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				if (!in[p->v])
				{
					if (q.empty()||dis[p->v]>dis[q.front()])
						q.push_back(p->v);
					else 
						q.push_front(p->v);
					in[p->v]=true;
				}
			}
	}
}

int ri=-1;
int main()
{
	freopen("bestspot.in","r",stdin);
	freopen("bestspot.out","w",stdout);
	scanf("%d%d%d",&P,&F,&C);
	for(int i=0;i<F;i++)
		scanf("%d",f+i);
	for(int i=0;i<C;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
	}
	for(int i=1;i<=P;i++)
	{
		spfa(i);
		int ans=0;
		for(int j=0;j<F&&ans<re;j++)
			if (dis[f[j]]!=oo)
				ans+=dis[f[j]];
			else ans=oo;
		if (ans<re)
			re=ans,ri=i;
	}
	printf("%d\n",ri);
	return 0;
}
