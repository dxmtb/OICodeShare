/*
ID: dxmtb
PROG: 情敌
TIME: 2010.11.18
STATE: Solved
MEMO: 背包
*/
#include <stdio.h>

#define MAXN 55
#define MAXV 105
#define oo 0x7fffffff

typedef long long LL;

LL N,M,V1,V2,sum;
LL d[MAXN][MAXV][MAXV],dd[MAXN][MAXV][MAXV];
LL adj[MAXN][MAXN];
bool nen[MAXN];
LL w[MAXN],v[MAXN];
LL fo[MAXN];
LL tmp=0;

inline void add(const LL &a,const LL &b)
{
	adj[a][++adj[a][0]]=b;
	nen[b]=true;
}

inline void Max(LL &a,LL b)
{
	if (b>a) a=b;
}

inline void dp(LL u)
{
	for(LL j=0;j<v[u];j++)
		for(LL k=0;k<=V2;k++)
			d[u][j][k]=-oo;
	for(LL j=v[u];j<=V1;j++)
		for(LL k=0;k<=V2;k++)
			d[u][j][k]=d[fo[u]][j-v[u]][k]+w[u];
	for(LL k=1;k<=adj[u][0];k++)
	{
		LL i=adj[u][k];
		fo[i]=tmp;
		tmp=i;
		for(LL j=0;j<=V1;j++)
			for(LL k=0;k<=V2;k++)
			{
				d[i][j][k]=d[fo[i]][j][k];
				if (j>=v[i])
					Max(d[i][j][k],d[fo[i]][j-v[i]][k]+w[i]);
				if (k>=2*v[i])
					Max(d[i][j][k],d[fo[i]][j][k-2*v[i]]+w[i]);
			}
	}	
	for(LL j=0;j<=V1;j++)
		for(LL k=0;k<=2*v[u];k++)
			dd[u][j][k]=-oo;
	for(LL j=0;j<=V1;j++)
		for(LL k=v[u]*2;k<=V2;k++)
			dd[u][j][k]=d[fo[u]][j][k-v[u]*2]+w[u];
	for(LL k=1;k<=adj[u][0];k++)
	{
		LL i=adj[u][k];
		for(LL j=0;j<=V1;j++)
			for(LL k=0;k<=V2;k++)
			{
				dd[i][j][k]=dd[fo[i]][j][k];
				if (k>=2*v[i])
					Max(dd[i][j][k],dd[fo[i]][j][k-2*v[i]]+w[i]);
			}
	}
	for(LL j=0;j<=V1;j++)
		for(LL k=0;k<=V2;k++)
		{
			Max(d[u][j][k],d[tmp][j][k]);
			Max(d[u][j][k],d[fo[u]][j][k]);
			Max(d[u][j][k],dd[u][j][k]);
		}
}

int main()
{
	freopen("rival.in","r",stdin);
	freopen("rival.out","w",stdout);
	scanf("%lld%lld",&V1,&V2);
	scanf("%lld%lld",&N,&M);
	for(LL i=1;i<=N;i++)
	{
		scanf("%lld%lld",w+i,v+i);
		sum+=w[i];
	}
	for(LL i=0;i<M;i++)
	{
		LL c,tot;
		scanf("%lld%lld",&c,&tot);
		for(LL j=0;j<tot;j++)
		{
			LL x;
			scanf("%lld",&x);
			add(c,x);
		}
	}
	fo[1]=tmp;
	for(LL i=1;i<=N;i++)
		if (!nen[i]&&adj[i][0]==0)
		{
			fo[i]=tmp;
			tmp=i;
			for(LL j=0;j<=V1;j++)
				for(LL k=0;k<=V2;k++)
				{
					d[i][j][k]=d[fo[i]][j][k];
					if (j>=v[i])
						Max(d[i][j][k],d[fo[i]][j-v[i]][k]+w[i]);
					if (k>=2*v[i])
						Max(d[i][j][k],d[fo[i]][j][k-2*v[i]]+w[i]);
				}
		}
		else if (adj[i][0])
		{
			fo[i]=tmp;
			tmp=i;
			dp(i);
			tmp=i;
		}
	printf("%lld\n",sum-d[tmp][V1][V2]);
	return 0;
}
