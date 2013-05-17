/*
ID: dxmtb
PROG: 吃豆人
TIME: 2010.7.7
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN=50,MAXM=MAXN*MAXN*2+2;
const int oo=0x7fffffff;

struct Node
{
	int u,c,w;//c 容量 w 费用
	Node *next,*f;
	Node(int a,int b,int c,Node *n):u(a),c(b),w(c),next(n){}
};

int n,m;
int sn,tn;
Node *g[MAXM];
Node *point[MAXM];
int dis[MAXM];
int way[MAXM];
int s,t;

inline int num(int x,int y,int e)
{
	return ((y-1)*n+x-1)*2+e;
}

bool spfa()
{
	bool in[MAXM];
	memset(in,false,sizeof(in));
	for(int i=0;i<=t;i++)
		dis[i]=-oo;
	queue<int> q;
	q.push(s);dis[s]=0;in[s]=true;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();in[now]=false;
		for(Node *p=g[now];p;p=p->next)
			if (p->c>0&&dis[p->u]<dis[now]+p->w)
			{
				dis[p->u]=dis[now]+p->w;
				if (!in[p->u])
					{q.push(p->u);in[p->u]=true;}
				way[p->u]=now;
				point[p->u]=p;
			}
	}
	if (dis[t]==-oo)return false;
	else return true;
}

int maxcost()
{
	int cost=0;
	while (spfa())
	{
		int delta=oo;
		for(int p=t;p!=s;p=way[p])
			if (point[p]->c<delta)
				delta=point[p]->c;
		for(int p=t;p!=s;p=way[p])
		{
			point[p]->c-=delta,point[p]->f->c+=delta,
			cost+=point[p]->w*delta;
			if (point[p]->w==1&&point[p]->c<-1)
				cerr<<"wrong"<<endl;
		}
	}
	return cost;
}

void add(int from,int to,int c,int w)
{
	g[from]=new Node(to,c,w,g[from]);
	g[to]=new Node(from,0,-w,g[to]);
	g[from]->f=g[to];
	g[to]->f=g[from];
}

int main()
{
	freopen("pacman.in","r",stdin);
	freopen("pacman.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&sn,&tn);
	s=0,t=2*m*n+1;
	for(int i=0;i<sn;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(s,num(x,y,1),w,0);
	}
	for(int i=0;i<tn;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(num(x,y,2),t,w,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int w;
			scanf("%d",&w);
			add(num(i,j,1),num(i,j,2),1,w);
			add(num(i,j,1),num(i,j,2),oo,0);
			if (i+1<=n)
				add(num(i,j,2),num(i+1,j,1),oo,0);
			if (j+1<=m)
				add(num(i,j,2),num(i,j+1,1),oo,0);
		}
	printf("%d\n",maxcost());
	return 0;
}
