/*
ID: dxmtb
PROG: TYVJ 二月月赛第一试 火焰巨魔的惆怅
TIME: 2011.02.11
STATE: Solved
MEMO: spfa
*/
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

typedef long long s64;

const int MAXN=50005;
const s64 oo=9223372036854775807ll;

struct Node
{
	int v;
	s64 w;
	Node *next;
	Node (int a,s64 b,Node *c):v(a),w(b),next(c){}
}*adj[MAXN];

inline void addedge(int u,int v,s64 w)
{
	adj[u]=new Node(v,w,adj[u]);
}

bool in[MAXN];
int S,T;
int N,M;
s64 dis[MAXN];
void spfa()
{
	queue<int> q;
	q.push(S);
	in[S]=true;
	dis[S]=1;
	for(int i=1;i<N;i++)
		dis[i]=oo;
	while(q.size())
	{
		int u=q.front();q.pop();
		s64 tmp;
		in[u]=false;
		for(Node *p=adj[u];p;p=p->next)
			if (dis[p->v]>
			   (tmp=max(s64(1),
			    s64(ceil((dis[u]-p->w)/double(2))))))
			{
				dis[p->v]=tmp;
				if (!in[p->v])
				{
					q.push(p->v);
					in[p->v]=true;
				}
			}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&N,&M);
	while(M--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		addedge(b,a,c);
	}
	S=N;T=1;
	spfa();
	printf("%lld\n",dis[1]);
	return 0;
}
