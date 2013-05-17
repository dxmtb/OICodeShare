/*
 * Problem: 1412: [ZJOI2009]狼和羊的故事
 * Time: 2011.07.22
 * Author: dxmtb
 * State: Solved
 * Memo: 最小割
*/
#include <cstdio>
#include <queue>
using namespace std;

#define MAXN 105
const int MAXM=MAXN*MAXN;
int a[MAXN][MAXN];
#undef MAXN
#define num(i,j) (((i)*M)+(j)+1)
const int way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const int oo=~0u>>2;

struct Node
{
	int v,c,p;
	Node *next,*back;
	Node (int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),p(_c),next(_next),back(_back){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXM],*cur[MAXM],pool[MAXM*10],*mem=pool;

inline void addedge(int u,int v,int c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int maxflow;
int S,T,lv[MAXM];
bool label()
{
	queue<int> q;
	for(int i=S;i<=T;i++)
		lv[i]=-1;
	lv[S]=0;
	q.push(S);
	while(q.size())
	{
		int u=q.front();q.pop();
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

int stack[MAXM],size;
Node *path[MAXM];
void augment()
{
	for(int i=S;i<=T;i++)
		cur[i]=adj[i];
	stack[0]=S,size=1;
	while(size)
	{
		int u=stack[size-1];
		if (u!=T)
		{
			for(Node *&p=cur[u];p;p=p->next)
				if (p->c>0 && lv[p->v]==lv[u]+1)
				{
					stack[size]=p->v;
					path[size++]=p;
					break;
				}
			if (cur[u]==NULL)
				size--,lv[u]=-1;
		}
		else
		{
			int delta=oo,k=-1;
			for(int i=1;i<size;i++)
				if (path[i]->c<delta)
					k=i,delta=path[i]->c;
			for(int i=1;i<size;i++)
				path[i]->c-=delta,
				path[i]->back->c+=delta;
			maxflow+=delta;
			size=k;
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
	scanf("%d%d",&N,&M);
	S=0,T=N*M+1;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			scanf("%d",a[i]+j);
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
		{
			for(int k=0;k<4;k++)
			{
				int ni=i+way[k][0],nj=j+way[k][1];
				if (ni>=0 && ni<N && nj>=0 && nj<M)
				{
					if (a[i][j]==0 || a[ni][nj]==0)
						addedge(num(i,j),num(ni,nj),1);
					else if (a[i][j]==1 && a[ni][nj]==2)
						maxflow++;
				}
			}
			if (a[i][j]==1)
				addedge(S,num(i,j),oo);
			else if (a[i][j]==2)
				addedge(num(i,j),T,oo);
		}
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
