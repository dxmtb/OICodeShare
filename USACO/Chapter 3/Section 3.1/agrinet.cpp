/*
ID: dxmtb1
PROG: agrinet
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=105;

struct Node 
{
	int u,v,w;
	Node(int a=0,int b=0,int c=0):u(a),v(b),w(c){}
};

int n,size=0;
int w[MAXN][MAXN];
bool in[MAXN];
Node heap[MAXN*MAXN];

void push(Node heap[],Node x)
{
	int i=++size;
	while (i>1&&x.w<heap[i/2].w)
	{
		heap[i]=heap[i/2];
		i=i/2;
	}
	heap[i]=x;
}

void del(Node heap[])
{
	heap[1]=heap[size--];
	int i=1;
	Node x=heap[1];
	while(i*2<=size)
	{
		int j=i*2+1;
		if (i*2+1>size||heap[i*2].w<heap[i*2+1].w)
			j--;
		if (heap[j].w<x.w)
			heap[i]=heap[j];
		i=j;
	}
	heap[i]=x;
}

void add(int u)
{
	for(int i=0;i<n;i++)
		if (!in[i]&&i!=u)
			push(heap,Node(u,i,w[u][i]));
}

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&w[i][j]);
}

void solve()
{
	add(0);
	int re=0;
	in[0]=true;
	for(int i=1;i<=n-1;i++)
	{
		while (in[heap[1].u]&&in[heap[1].v])
			del(heap);
		Node now=heap[1];
		del(heap);
		if (!in[now.u])
		{
			add(now.u);
			in[now.u]=true;
		}
		else
		{
			add(now.v);
			in[now.v]=true;
		}
		re+=now.w;
	}
	printf("%d\n",re);
}

int main() 
{
	freopen("agrinet.in","r",stdin);
	freopen("agrinet.out","w",stdout);
	init();
	solve();
	return 0;
}
