/*
ID: dxmtb
PROG: 运输问题4
TIME: 2010.9.4
STATE: Solved
MEMO: 费用流
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=100;
const int oo=0x7fffffff;

int n,s,t;
int c[MAXN][MAXN],w[MAXN][MAXN];
int dis[MAXN];
int fo[MAXN];

bool label()
{
	queue<int> q;
	bool in[MAXN];
	for(int i=0;i<n;i++)
		dis[i]=oo,in[i]=false;
	dis[s]=0;in[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int now=q.front();q.pop();
		in[now]=false;
		for(int i=0;i<n;i++)
			if (c[now][i]>0&&dis[i]>dis[now]+w[now][i])
			{
				dis[i]=dis[now]+w[now][i];
				fo[i]=now;
				if (!in[i])
				{
					q.push(i);
					in[i]=true;
				}
			}
	}
	return dis[t]!=oo;
}

int minw;
void agu()
{
	int delta=oo;
	for(int u=t,v=fo[t];u!=s;u=v,v=fo[v])
		if (c[v][u]<delta)
			delta=c[v][u];
	for(int u=t,v=fo[t];u!=s;u=v,v=fo[v])
		c[v][u]-=delta,c[u][v]+=delta;
	minw+=dis[t]*delta;
}

void solve()
{
	while(label())
		agu();
}

int main()
{
	freopen("maxflowd.in","r",stdin);
	freopen("maxflowd.out","w",stdout);
	scanf("%d%d%d",&n,&s,&t);
	s--,t--;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			scanf("%d%d",c[i]+j,w[i]+j);
			w[j][i]-=w[i][j];
		}
	solve();
	printf("%d\n",minw);
	return 0;
}
	
