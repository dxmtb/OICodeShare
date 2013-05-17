/*
 * Problem: [HNOI2008]神奇的国度
 * Time: 2011.05.04
 * Author: dxmtb
 * State: Solved
 * Memo: 弦图
*/
#include <cstdio>

const int MAXN=10005,MAXM=1000005;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):v(_v),next(_next){}
	Node (){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXM*2],*mem=pool;

inline void addedge(int u,int v)
{
	adj[u]=new (mem++)Node(v,adj[u]);
	adj[v]=new (mem++)Node(u,adj[v]);
}

struct List
{
	int v;
	List *next,*back;
	List(){}
	void *operator new (size_t,void *p){return p;}
}pool1[MAXN],pool2[MAXN];

List *L1;
List *L2[MAXN];

inline void connect(List *a,List *b)
{
	a->next=b;
	b->back=a;
}

inline void push_back(List *&L,List *mem)
{
	if (L==NULL)
	{
		L=mem;
		L->next=L->back=L;
	}
	else
	{
		List *p=L->back;
		connect(p,mem);
		connect(mem,L);
	}
}

inline void pop_back(List *&L)
{
	if (L->next==L)
		L=NULL;
	else
		connect(L->back->back,L);
}

int N;
int pos[MAXN];

void init()
{
	for(int i=0;i<=N;i++)
		pool1[i].v=pool2[i].v=i;
	L1=pool1;
	L1->next=L1->back=L1;
	for(int i=1;i<=N;i++)
		push_back(L2[0],pool2+i);
}

inline void up(int u)
{
	int x=pos[u];
	pos[u]++;
	//check L1
	//insert x+1 if not exist
	if (pool1[x].next!=&pool1[x+1])
	{
		connect(&pool1[x+1],pool1[x].next);
		connect(&pool1[x],&pool1[x+1]);
	}
	//remove u from x
	if (L2[x]->next!=L2[x])//after remove u ,x is not empty
	{
		connect(pool2[u].back,pool2[u].next);
		if (L2[x]==&pool2[u])
			L2[x]=pool2[u].next;
	}
	else
	{
		connect(pool1[x].back,pool1[x].next);
		if (L1==&pool1[x])
			L1=pool1[x].next;
		L2[x]=NULL;
	}
	//insert u to x+1
	push_back(L2[x+1],pool2+u);
}

int ind[MAXN];
int M;

int main()
{
	freopen("1006.in","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	init();
	int re=1;
	for(int i=N;i;i--)
	{
		int j=L1->back->v;
		int u=L2[j]->back->v;
		ind[u]=i;
		pop_back(L2[j]);
		if (L2[j]==NULL)
			pop_back(L1);
		int ans=1;
		for(Node *p=adj[u];p;p=p->next)
			if (!ind[p->v])
				up(p->v);
			else
				ans++;
		if (ans>re)
			re=ans;
	}
	printf("%d\n",re);
	return 0;
}
