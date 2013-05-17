#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=100;

bool g[MAXN+1][MAXN+1];
int n,m,L,q;

void init()
{
	scanf("%d%d%d",&n,&m,&L);
	for(int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a][b]=true;
	}
	scanf("%d",&q);
}

int dp(int s,int t)
{
	int d[MAXN+1][MAXN+1];
	memset(d,0,sizeof(d));
	d[0][s]=1;
	for(int i=1;i<=L;i++)
	{
		memset(d[i&1],0,sizeof(d[i%1]));
		for(int a=1;a<=n;a++)
			if (d[1-(i&1)][a])
			for(int b=1;b<=n;b++)
				if (g[a][b])
					d[i&1][b]+=d[1-(i&1)][a];
	}
	return d[L&1][t];
}

int main()
{
	freopen("merchant.in","r",stdin);
	freopen("merchant.out","w",stdout);
	init();
	for(int i=0;i<q;i++)
	{
		int A,B;
		scanf("%d%d",&A,&B);
		printf("%d\n",dp(A,B));
	}
	return 0;
}
