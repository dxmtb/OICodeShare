/*
ID: dxmtb
PROG: NOIP2006 金明的预算方案
TIME: 2010.8.3
STATE: Solved
MEMO: 背包
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=3210,MAXM=62;

int n,m;
int v[MAXM],w[MAXM],c[MAXM][3],q[MAXN];
int d[MAXM][MAXN];

void init()
{
	scanf("%d%d",&n,&m);
	n=n/10;
	for(int i=1;i<=m;i++)
	{
		int p;
		scanf("%d%d%d",&v[i],&p,&q[i]);
		v[i]=v[i]/10;
		w[i]=v[i]*p;
		if (q[i])
			c[q[i]][++c[q[i]][0]]=i;
	}
}

int max(int a,int b)
{
	if (a>b)return a;
	return b;
}

void solve()
{
	int form=0;
	for(int i=1;i<=m;i++)
		if (!q[i])
		{
			for(int j=0;j<=n;j++)
			{
				d[i][j]=max(d[i][j],d[form][j]);
				if (j>=v[i])
					d[i][j]=max(d[i][j],d[form][j-v[i]]+w[i]);
				for(int k=1;k<=c[i][0];k++)
				{
					int child=c[i][k];
					if (j>=v[child]+v[i])
						d[i][j]=max(d[i][j],d[form][j-v[child]-v[i]]+w[child]+w[i]);
				}
				if (c[i][0]==2)
				{
					int c1=c[i][1],c2=c[i][2];
					if (j>=v[c1]+v[c2]+v[i])
						d[i][j]=max(d[i][j],d[form][j-v[c1]-v[c2]-v[i]]+w[c1]+w[c2]+w[i]);
				}
			}
			form=i;
		}
	printf("%d\n",d[form][n]*10);
}

int main() 
{
	freopen("budget.in","r",stdin);
	freopen("budget.out","w",stdout);
	init();
	solve();
	return 0;
}
