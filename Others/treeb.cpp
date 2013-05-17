/*
ID: dxmtb
PROG: treeb
TIME: 2010.11.9
STATE: Solved
MEMO: 树形dp
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=1005;

int N;
int adj[MAXN][MAXN];
int d[MAXN][2];
long long g[MAXN][2];

void dp(int u,int father)
{
	g[u][0]=1;
	for(int i=1;i<=adj[u][0];i++)
	{
		const int &v=adj[u][i];
		dp(v,u);
		if (d[v][0]<d[v][1])
			d[u][0]+=d[v][1],g[u][0]*=g[v][1];
		else if (d[v][0]>d[v][1])
			d[u][0]+=d[v][0],g[u][0]*=g[v][0];
		else d[u][0]+=d[v][0],g[u][0]*=(g[v][0]+g[v][1]);
	}
	for(int i=1;i<=adj[u][0];i++)
	{
		const int &v=adj[u][i];
		int nd=d[u][0]-max(d[v][0],d[v][1])+d[v][0]+1;
		unsigned long long ng=g[u][0];
		if (d[v][0]<d[v][1])
			ng=(g[u][0]/g[v][1])*g[v][0];
		else if (d[v][0]>d[v][1])
			ng=(g[u][0]/g[v][0])*g[v][0];
		else if (d[v][0]==d[v][1])
			ng=g[u][0]/(g[v][0]+g[v][1])*g[v][0];
		if (d[u][1]<nd)
			d[u][1]=nd,g[u][1]=ng;
		else if (d[u][1]==nd)
			g[u][1]+=ng;
	}
}

int main()
{
	freopen("treeb.in","r",stdin);
	freopen("treeb.out","w",stdout);
	cin>>N;
	for(int i=0;i<N;i++)
	{
		int j;
		cin>>j;cin>>adj[j][0];
		for(int k=1;k<=adj[j][0];k++)
			cin>>adj[j][k];
	}
	dp(1,0);
	if (d[1][0]>d[1][1])
		cout<<d[1][0]<<endl<<g[1][0]<<endl;
	else if (d[1][0]<d[1][1])
		cout<<d[1][1]<<endl<<g[1][1]<<endl;
	else
		cout<<d[1][0]<<endl<<g[1][0]+g[1][1]<<endl;
	return 0;
}
