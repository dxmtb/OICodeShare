/*
PROG: apple
LANG: C++
ID: dxmtb1
*/
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN=100005;
const int oo=0x7fffffff;

struct Node
{
	int v,w;
	Node *next;
	Node(int a,int b,Node* c):v(a),w(b),next(c){}
}*adj[MAXN];

void addedge(int u,int v,int w)
{
	adj[u]=new Node(v,w,adj[u]);
	adj[v]=new Node(u,w,adj[v]);
}

int M,N,S,T1,T2;

bool in[MAXN];
void spfa(int s,int dis[])
{
	deque<int>q;
	for(int i=1;i<=N;i++)
		dis[i]=oo;
	q.push_back(s);in[s]=true;
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>dis[u]+p->w)
			{
				dis[p->v]=dis[u]+p->w;
				if (!in[p->v])
				{
					if (q.empty()||dis[q.front()]<dis[p->v])
						q.push_back(p->v);
					else q.push_front(p->v);
				}
			}
	}
}

int dis[2][MAXN];
int main()
{
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	scanf("%d%d%d%d%d",&M,&N,&S,&T1,&T2);
	while(M--)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
	}
	spfa(S,dis[0]);
	spfa(T1,dis[1]);
	printf("%d\n",min(dis[0][T1],dis[0][T2])+dis[1][T2]);
	return 0;
}
