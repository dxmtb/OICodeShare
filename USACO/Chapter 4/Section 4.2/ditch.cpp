/*
ID: dxmtb1
PROG: ditch
LANG: C++
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=200,MAXM=200;
const int oo=0x7fffffff;

int n,m;
int c[MAXN][MAXN];
int s,t;
int maxflow;
int dis[MAXN];

bool dinic_label()
{
	queue<int> q;
	for(int i=1;i<n;i++)
		dis[i]=oo;
	q.push(s);
	dis[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<n;i++)
			if(c[u][i]>0&&dis[i]==oo)
			{
				dis[i]=dis[u]+1;
				q.push(i);
			}
		if (dis[t]!=oo)
			return true;
	}
	return false;
}

void dinic_argu()
{
	int stack[MAXN],stop,i;
	stack[stop=0]=s;
	while(stop>=0)
	{
		int u=stack[stop];
		if (u==t)
		{
			int delta=oo;
			for(i=stop;i;--i)delta=min(delta,c[stack[i-1]][stack[i]]);
			for(i=stop;i;--i)
			{
				c[stack[i-1]][stack[i]]-=delta;
				c[stack[i]][stack[i-1]]+=delta;
				if (c[stack[i-1]][stack[i]]==0)
					stop=i-1;
			}
			maxflow+=delta;
		}
		else
		{
			for(i=0;i<n;i++)
				if (c[u][i]>0&&dis[i]==dis[u]+1)
				{
					stack[++stop]=i;
					break;
				}
			if (i==n)
				stop--,dis[u]=oo;
		}
	}
}

void dinic()
{
	while(dinic_label())
		dinic_argu();
}

int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=0,a,b;i<m;i++)
	{
		scanf("%d%d%d",&a,&b,&t);
		--a;--b;
		c[a][b]+=t;
	}
	s=0,t=n-1;
	dinic();
	printf("%d\n",maxflow);
	return 0;
}
