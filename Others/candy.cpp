/*
ID: dxmtb
PROG: Perform巡回演出
TIME: 2010.10.8
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define init(x) memset(x,0,sizeof(x))

const int MAXN=13,MAXK=1003,MAXD=33;
const int oo=100000000;

int d[MAXK][MAXN];
int path[MAXK][MAXN];
int cost[MAXN][MAXK][MAXD];
int D[MAXN][MAXK];
int n,K;

int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	while(true)
	{
		scanf("%d%d",&n,&K);
		if (!n&&!K)break;
		init(cost);
		init(d);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				if (i==j) continue;
				scanf("%d",D[i]+j);
				for(int k=0;k<D[i][j];k++)
					scanf("%d",cost[i][j]+k);
			}
		for(int i=0;i<=K;i++)
			for(int j=0;j<n;j++)
				d[i][j]=oo;
		d[0][0]=0;
		for(int i=1;i<=K;i++)
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					if (j!=k)
					{
						int t=d[i-1][k]+cost[k][j][(i-1)%D[k][j]];
						if (t!=d[i-1][k]&&t<d[i][j])
							d[i][j]=t,path[i][j]=k;
					}
		if (d[K][n-1]>=oo)
			printf("0\n");
		else printf("%d\n",d[K][n-1]);
	}
	return 0;
}
