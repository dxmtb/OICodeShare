/*
ID: dxmtb
PROG: 运输问题2
TIME: 2010.9.9
STATE: Solved
MEMO: 上下界网络流
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN=102;
const int oo=200000000;

int n,s,t,c[MAXN][MAXN],b[MAXN][MAXN];
int flow[MAXN][MAXN];
int maxflow,tflow,t1,t2;

void build()
{
	s=0;t=n+1;
	maxflow+=c[1][n];
	b[1][n]=b[n][1]=0;
	c[1][n]=c[n][1]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			c[s][i]+=b[j][i];
			c[i][t]+=b[i][j];
			c[i][j]-=b[i][j];
		}
	c[1][n]=c[n][1]=oo;
	n+=2;
}

int dis[MAXN];
bool label()
{
	queue<int> q;
	for(int i=s;i<=t;i++)
		dis[i]=oo;
	dis[s]=0;q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=s;i<=t;i++)
			if (c[u][i]>0&&dis[i]==oo)
			{
				dis[i]=dis[u]+1;
				q.push(i);
			}
		if (dis[t]!=oo)return true;
	}
	if (dis[t]!=oo)return true;
	return false;
}

void agu(int &flowt)
{
	int stack[MAXN],stop,i;
	stack[0]=s;stop=1;
	while(stop)
	{
		int u=stack[stop-1];
		if (u==t)
		{
			int delta=oo;
			for(i=stop-1;i;i--)
				if (c[stack[i-1]][stack[i]]<delta)
					delta=c[stack[i-1]][stack[i]];
			for(i=stop-1;i;i--)
			{
				c[stack[i-1]][stack[i]]-=delta;
				flow[stack[i-1]][stack[i]]+=delta;
				c[stack[i]][stack[i-1]]+=delta;
				flow[stack[i]][stack[i-1]]-=delta;
				if (c[stack[i-1]][stack[i]]==0)
					stop=i-1;
			}
			flowt+=delta;
		}
		else
		{
			for(i=s;i<=t;i++)
				if (c[u][i]>0&&dis[u]+1==dis[i])
				{
					stack[stop++]=i;
					break;
				}
			if (i==t+1)
				dis[u]=-1,stop--;
		}
	}
}

void dinic(int &flow)
{
	while(label())
		agu(flow);
}

int flow2;
void check()
{
	for(int i=s+1;i<t;i++)
		if (c[s][i])
		{
			printf("No solution");
			exit(0);
		}
}

void rebuild()
{
	n-=2;
	s=1,t=n;
	c[s][t]=0;
	c[t][s]=0;
	for(int i=1;i<=n;i++)
		c[0][i]=c[i][0]=0,
		c[i][n+1]=c[n+1][i]=0;
}

int main()
{
	freopen("maxflowb.in","r",stdin);
	freopen("maxflowb.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d%d",b[i]+j,c[i]+j);
			if (c[i][j]<b[i][j])
			{
				printf("No solution\n");
				return 0;
			}
		}
	build();
	dinic(flow2);
	check();
	rebuild();
	dinic(flow2);
//	printf("%d\n",maxflow);
	for(int i=2;i<t;i++)
		maxflow+=flow[s][i]+b[s][i];
	printf("%d\n",maxflow);
	return 0;
}
