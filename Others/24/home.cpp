/*
ID: dxmtb
PROG: 线性规划与网络流24题 星际转移问题
TIME: 2011.02.08
STATE: Solved
MEMO: 分层建图
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=5000;
const int oo=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(){}
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
	void *operator new (unsigned ,void *p){return p;}
}*adj[MAXN],pool[MAXN],*mem=pool;

inline void addedge(int u,int v,int c)
{
//	printf("add %d %d %d",u,v,c);
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

inline void Min(int &a,const int &b)
{
	if (a>b)
		a=b;
}

int S,T;

int lv[MAXN];
bool label()
{
	queue<int> q;
	memset(lv,-1,sizeof(lv));
	lv[S]=0;
	q.push(S);
	while(q.size())
	{
		int u=q.front();q.pop();
		int tmp=lv[u]+1;
		for(Node *p=adj[u];p;p=p->next)
			if (p->c&&lv[p->v]==-1)
			{
				lv[p->v]=tmp;
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
					path[size]=p;
					stack[size++]=p->v;
					break;
				}
			if (!p)
				lv[u]=-1,size--;	
		}
		else
		{
			int delta=oo;
			for(int i=size-1;i;i--)
					Min(delta,path[i]->c);
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

int N,M,K,P[MAXN],R[MAXN];
int SS[MAXN][MAXN];
int main()
{
	freopen("home.in","r",stdin);
	freopen("home.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1,*p=P+1,*r=R+1;i<=M;i++,p++,r++)
	{
		scanf("%d%d",p,r);
		for(int j=0;j<*r;j++)
		{
			scanf("%d",SS[i]+j);
			if (SS[i][j]==-1)
				SS[i][j]=N+1;
		}
		if (*r==1||*p==0)
			*r=0;
		if (*r)
		{
			for(int j=0;j<R[i]-1;j++)
				addedge(SS[i][j],SS[i][j+1],P[i]);
			addedge(SS[i][R[i]-1],SS[i][0],P[i]);
		}
	}
	S=0,T=N+1;
	if (label())
	{
		memset(adj,0,sizeof(adj));
		mem=pool;
		S=0,T=N+1+N+2;
		int ans=1;
		while(true)
		{
			for(int i=0;i<=N+1;i++)
				addedge(i+(N+2)*(ans-1),
					i+(N+2)*ans,oo);
			for(int i=1;i<=M;i++)
			if (R[i])
			{
				int j=ans-1;
				j%=R[i];	
				int jj=j+1;
				jj%=R[i];
				addedge(SS[i][j]+(N+2)*(ans-1),
					SS[i][jj]+(N+2)*ans,P[i]);
			}
			dinic();
			if (maxflow>=K)
			{
				printf("%d\n",ans);
				return 0;
			}
			ans++;
			T+=N+2;
		}
	}
	else
		printf("0\n");
	return 0;
}
