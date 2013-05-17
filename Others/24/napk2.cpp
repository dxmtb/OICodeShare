/*
ID: dxmtb
PROG: 线性规划与网络流24题 餐巾计划问题
TIME: 2011.02.07
STATE: Solved
MEMO: 最小费用流可行流
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=2000;
const int oo=0x7fffffff;
const int maxint=0x3F3F3F3F;

struct Node
{
	int v,c,w;
	Node *next,*back;
	Node(){}
	Node(int p,int q,int r,Node *n,Node *m=NULL):
	     v(p),c(q),w(r),next(n),back(m){}
	void * operator new (unsigned ,void *p){return p;}
}*adj[MAXN];

Node *mem;
inline void addedge(int u,int v,int c,int w)
{
//	printf("add %d %d %d %d\n",u,v,c,w);
	adj[u]=new(mem++) Node(v,c,w,adj[u]);
	adj[v]=new(mem++) Node(u,0,-w,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int d[MAXN],S,T;
int mincost,piS;
bool v[MAXN];
 
int aug(int no, int m)
{
    if (no == T) return mincost += piS * m, m;
    v[no] = true;
    int l = m;
    for (Node *i = adj[no]; i; i = i->next)
        if (i->c && !i->w && !v[i->v])
        {
            int d = aug(i->v, l < i->c ? l : i->c);
            i->c -= d, i->back->c += d, l -= d;
            if (!l) return m;
        }
    return m - l;
}
 
bool modlabel()
{
    static int d[MAXN]; memset(d, 0x3F, sizeof(d)); d[T] = 0;
    static deque<int> Q; Q.push_back(T);
    while(Q.size())
    {
        int dt, no = Q.front(); Q.pop_front();
        for(Node *i = adj[no]; i; i = i->next)
            if(i->back->c && (dt = d[no] - i->w) < d[i->v])
                (d[i->v] = dt) <= d[Q.size() ? Q.front() : 0]
                    ? Q.push_front(i->v) : Q.push_back(i->v);
    }
    for(int i = S; i <= T; ++i)
        for(Node *j = adj[i]; j; j = j->next)
            j->w += d[j->v] - d[i];
    piS += d[S];
    return piS<0;
}
 
void solve()
{
        while(modlabel())
            do memset(v, 0, sizeof(v));
            while(aug(S, maxint));
}

int N,p,m,f,n,s;
int main()
{
	freopen("napk.in","r",stdin);
	freopen("napk.out","w",stdout);
	scanf("%d%d%d%d%d%d",&N,&p,&m,&f,&n,&s);
	int sum=0;
	S=0;T=2*N+1;
	mem=new Node[N*13];
	for(int i=1;i<=N;i++)
	{
		int a;
		scanf("%d",&a);
		addedge(i*2-1,i*2,a,-p);
		/*addedge(S,i*2-1,a,0);
		addedge(i*2,T,a,0);
		addedge(S,i*2,oo,p);
		if (i!=N)
			addedge(i*2-1,i*2+1,oo,0);
		if (i+m<=N)
			addedge(i*2-1,(i+m)*2,oo,f);
		if (i+n<=N)
			addedge(i*2-1,(i+n)*2,oo,s);*/
		sum+=a;
	}
	
	addedge(S,1,oo,p);
	for(int i=1;i<N;i++)
		addedge(i*2-1,i*2+1,oo,0);
	for(int i=1;i<=N-m;i++)
		addedge(i*2,(i+m)*2-1,oo,f);
	for(int i=1;i<=N-n;i++)
		addedge(i*2,(i+n)*2-1,oo,s);
	for(int i=1;i<=N;i++)
		addedge(i*2,T,oo,0);
		
	solve();
	printf("%d\n",mincost+p*sum);
//	printf("%d\n",maxflow);
	return 0;
}
