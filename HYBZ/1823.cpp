/*
 * Problem: [JSOI2010]满汉全席
 * Time: 2011.04.07
 * Author: dxmtb
 * State: Solved
 * Memo: 2-SAT
*/
#include <cstdio>
#include <cstring>

const int MAXN=1000;

struct Node
{
	int v;
	Node *next;
	Node (int _v,Node *_next):
		v(_v),next(_next){}
	Node (){}
}*adj[MAXN];

inline void addedge(int u,int v)
{
	adj[u]=new Node(v,adj[u]);
}

int dfn[MAXN],low[MAXN],s[MAXN];
int size,ind;
bool in[MAXN],used[MAXN];

bool dfs(int u)
{
	dfn[u]=low[u]=++ind;
	s[size++]=u;
	in[u]=true;
	for(Node *p=adj[u];p;p=p->next)
		if (!dfn[p->v])
		{
			if (!dfs(p->v))
				return false;
			if (low[p->v]<low[u])
				low[u]=low[p->v];
		}
		else if (in[p->v] && dfn[p->v]<low[u])
			low[u]=dfn[p->v];
	if (dfn[u]==low[u])
	{
		int v;
		memset(used,false,sizeof(used));
		do
		{
			v=s[--size];
			in[v]=false;
			if (used[v/2])
				return false;
			used[v/2]=true;
		}while(v!=u);
	}
	return true;
}

int N,M;
int main()
{
	freopen("1823.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<2*N;i++)
			adj[i]=NULL;
		while(M--)
		{
			int u,v;
			int _u,_v,__u,__v;
			char ch1,ch2;
			scanf(" %c%d %c%d",&ch1,&u,&ch2,&v);
			u--,v--;
			if (ch1=='m') _u=2*u,__u=2*u+1;
			else _u=2*u+1,__u=2*u;
			if (ch2=='m') _v=2*v,__v=2*v+1;
			else _v=2*v+1,__v=2*v;
			addedge(__u,_v);
			addedge(__v,_u);
		}
		ind=0;size=0;
#define clear(x) memset((x),0,sizeof(x))
		clear(dfn);clear(low);clear(s);
		clear(in);clear(used);
		for(int i=0;i<2*N;i++)
			if (!dfn[i])
				if (!dfs(i))
				{
					printf("BAD\n");
					goto OUT;
				}
		printf("GOOD\n");
OUT:;
	}
	return 0;
}
