/*
 * Problem: 2150: 部落战争
 * Time: 2011.07.21
 * Author: dxmtb
 * State: Solved
 * Memo: 网络流
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=5005;
const int oo=~0u>>2;

struct Node
{
	int v,c;
	Node *next,*back;
	Node(int _v,int _c,Node *_next,Node *_back=NULL):
		v(_v),c(_c),next(_next),back(_back){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN*2],*cur[MAXN*2],pool[MAXN*16],*mem=pool;

inline void addedge(int u,int v,int c)
{
	adj[u]=new (mem++)Node(v,c,adj[u]);
	adj[v]=new (mem++)Node(u,0,adj[v],adj[u]);
	adj[u]->back=adj[v];
}

int S,T;
int lv[MAXN];
bool label()
{
	for(int i=S;i<=T;i++)
		lv[i]=-1;
	lv[S]=0;
	queue<int> q;
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

int maxflow;
int stack[MAXN],size;
Node *path[MAXN];
void augment()
{
	stack[0]=S,size=1;
	for(int i=S;i<=T;i++)
		cur[i]=adj[i];
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
				lv[u]=-1,size--;
		}
		else
		{
			int delta=oo,k=-1;
			for(int i=1;i<size;i++)
				if (path[i]->c<delta)
				{
					delta=path[i]->c;
					k=i;
				}
			for(int i=1;i<size;i++)
			{
				path[i]->c-=delta;
				path[i]->back->c+=delta;
			}
			size=k;
			maxflow+=delta;
		}
	}
}

int N,M,R,C;
char str[55][55];
int main()
{
	scanf("%d%d%d%d",&N,&M,&R,&C);
	for(int i=0;i<N;i++)
		scanf(" %s",str[i]);
	S=0,T=2*N*M+1;
	int tot=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if (str[i][j]=='.')
			{
				tot++;
				addedge(S,(i*M+j)*2+1,1);
				addedge((i*M+j)*2+2,T,1);
				if (i+R<N && j+C<M)
					addedge((i*M+j)*2+1,((i+R)*M+j+C)*2+2,1);
				if (i+R<N && j-C>=0)
					addedge((i*M+j)*2+1,((i+R)*M+j-C)*2+2,1);
				swap(R,C);
				if (i+R<N && j+C<M)
					addedge((i*M+j)*2+1,((i+R)*M+j+C)*2+2,1);
				if (i+R<N && j-C>=0)
					addedge((i*M+j)*2+1,((i+R)*M+j-C)*2+2,1);
				swap(R,C);
			}
	while(label())
		augment();
	printf("%d\n",tot-maxflow);
	return 0;
}
