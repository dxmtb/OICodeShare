/*
ID: dxmtb
PROG: 联赛
TIME: 2010.7.8
STATE: Solved
MEMO: 网络流
*/
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN=61,MAXM=MAXN*MAXN+MAXN+3;
const int MAXINT=0x7fffffff;

struct Node
{
	int v,c;
	Node *next,*f;
	Node(int a,int b,Node *n,Node *d=0):v(a),c(b),next(n),f(d){};
}*c[MAXM];

int n;
int w[MAXN],a[MAXN][MAXN],d[MAXN];
int s,t;
int dis[MAXM];
int maxflow;
bool first=true;

bool lable()
{
	bool in[MAXM];
	memset(in,false,sizeof(in));
	queue<int> q;
	q.push(s);
	in[s]=true;
	for(int i=s;i<=t;i++)
		dis[i]=MAXINT;
	dis[s]=0;
	while (!q.empty())
	{
		int now=q.front();
//`		printf("%d\n",now);
		q.pop();in[now]=false;
		for(Node *p=c[now];p;p=p->next)
			if (p->c>0&&dis[now]+1<dis[p->v])
			{
				dis[p->v]=dis[now]+1;
				if(!in[p->v])
				{
					q.push(p->v);
					in[p->v]=true;
				}
//				printf("%d\n",p->v);
			}
	}
	if (dis[t]!=MAXINT)
		return true;
	return false;
}

void agument()
{
	int delta,stop=1;
	int stack[MAXN];
	Node *way[MAXN];
	stack[stop=1]=s;
	while (stop)
	{
		int now=stack[stop];
		if (now==t)
		{
			delta=MAXINT;
			for(int i=stop;i>1;i--)
				if (way[i]->c<delta)
					delta=way[i]->c;
			for(int i=stop;i>1;i--)
			{
				way[i]->c-=delta,
				way[i]->f->c+=delta;
				if (!way[i]->c)
					stop=i-1;
			}
			maxflow+=delta;
		}
		else
		{
			Node *p;
			for(p=c[now];p;p=p->next)
				if (p->c>0&&dis[p->v]==dis[now]+1)
					break;
			if (!p)
				stop--,dis[now]=MAXINT;
			else
				stack[++stop]=p->v,way[stop]=p;
		}
	}
}

void dinic()
{
	maxflow=0;
	while (lable())
		agument();
}

inline int num(int i,int j)
{
	return n+(i-1)*n+j;
}

void add(int a,int b,int v)
{
	c[a]=new Node(b,v,c[a]);
	c[a]->f=c[b]=new Node(a,0,c[b],c[a]);
}

int main()
{
	freopen("kleague.in","r",stdin);
	freopen("kleague.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",w+i,d+i);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	s=0,t=n+n*n+1;
	for(int k=1;k<=n;k++)
	{
		int win=w[k];
		int temp=0;
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if (i!=k&&j!=k)
				{
					add(i,num(i,j),MAXINT);
					add(j,num(i,j),MAXINT);
					add(num(i,j),t,a[i][j]);
					temp+=a[i][j];
				}
				else win+=a[i][j];
		bool flag=true;
		for(int i=1;i<=n;i++)
			if (i!=k)
			{
				if (w[i]<=win)
					add(s,i,win-w[i]);
				else {flag=false;break;}
			}
		if (!flag)continue;
		dinic();
		if (maxflow==temp)
		{
			if (first){printf("%d",k);first=false;}
			else printf(" %d",k);
		}
	}
	printf("\n");
	return 0;
}
