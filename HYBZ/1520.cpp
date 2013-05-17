/*
 * Problem: [POI2006]Szk-Schools 
 * Time: 2011.04.13
 * Author: dxmtb
 * State: Solved
 * Memo: KMÀ„∑®
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
using namespace std;

const int MAXN=500;
const int oo=200005;

struct Node
{
	int v,w;
	Node *next;
	Node(){}
	Node(int _v,int _w,Node *_next):v(_v),w(_w),next(_next){}
	void *operator new (size_t,void *p){return p;}
}*adj[MAXN],pool[MAXN*MAXN],*mem=pool;
	
inline void addedge(int u,int v,int w)
{
	adj[u]=new (mem++)Node(v,w,adj[u]);
}

int lx[MAXN],ly[MAXN],matchy[MAXN],matchw[MAXN],slack[MAXN];
bool visx[MAXN],visy[MAXN];

bool find(int x)
{
	visx[x]=true;
	for(Node *p=adj[x];p;p=p->next)
		if (!visy[p->v])
		{
			if (lx[x]+ly[p->v]-p->w==0)
			{
				visy[p->v]=true;
				if (matchy[p->v]==-1 || find(matchy[p->v]))
				{
					matchy[p->v]=x;
					matchw[p->v]=p->w;
					return true;
				}
			}
			else if (lx[x]+ly[p->v]-p->w<slack[p->v])
				slack[p->v]=lx[x]+ly[p->v]-p->w;
		}
	return false;
}

int N,mincost;
void KM()
{
	for(int i=0;i<N;i++)
		for(Node *p=adj[i];p;p=p->next)
			if (p->w>lx[i])
				lx[i]=p->w;
	memset(matchy,-1,sizeof(matchy));
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			slack[j]=oo;
		while(true)
		{
			memset(visx,false,sizeof(visx));
			memset(visy,false,sizeof(visy));
			if (find(i))
				break;
			int mins=oo;
			for(int i=0;i<N;i++)
				if (!visy[i] && slack[i]<mins)
					mins=slack[i];
			for(int i=0;i<N;i++)
				if (visx[i])
					lx[i]-=mins;
			for(int i=0;i<N;i++)
				if (visy[i])
					ly[i]+=mins;
				else
					slack[i]-=mins;
		}
		if (matchw[i]==-oo)
		{
			printf("NIE\n");
			exit(0);
		}
	}
	for(int i=0;i<N;i++)
		mincost+=-matchw[i];
}

int main()
{
	freopen("1520.in","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		int m,s,t,k;
		scanf("%d%d%d%d",&m,&s,&t,&k);
		s--,t--,m--;
		for(int j=0;j<s;j++)
			addedge(i,j,-oo);
		for(int j=s;j<=t;j++)
			addedge(i,j,-k*abs(j-m));
		for(int j=t+1;j<N;j++)
			addedge(i,j,-oo);
	}
	KM();
	printf("%d\n",mincost);
	return 0;
}
