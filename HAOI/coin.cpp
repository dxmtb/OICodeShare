/*
ID: dxmtb
PROG: HAOI 硬币购物
TIME: 2011.03.19
STATE: Solved
MEMO: dp 容斥原理
*/
#include <cstdio>

const int MAXN=100005;


int c[4];
long long d[4][MAXN];
int tot,s=100000;

int main()
{
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
	scanf("%d%d%d%d%d",c,c+1,c+2,c+3,&tot);
	for(int k=0;k*c[0]<=s;k++)
		d[0][k*c[0]]=1;
	for(int i=1;i<4;i++)
	{
		for(int j=0;j<c[i];j++)
		{
			long long sum=0;
			for(int k=0;k*c[i]+j<=s;k++)
			{
				sum+=d[i-1][j+k*c[i]];
				d[i][j+k*c[i]]+=sum;
			}
		}
	}
	long long *f=d[3];
	while(tot--)
	{
		int a[4],ns;
		scanf("%d%d%d%d%d",a,a+1,a+2,a+3,&ns);
		long long re=f[ns];
		int b[4]={(a[0]+1)*c[0],(a[1]+1)*c[1],(a[2]+1)*c[2],(a[3]+1)*c[3]};
#define sub(x) if (x>=0) re-=f[x]
#define add(x) if (x>=0) re+=f[x]
		sub(ns-b[0]);
		sub(ns-b[1]);
		sub(ns-b[2]);
		sub(ns-b[3]);
		add(ns-b[0]-b[1]);
		add(ns-b[0]-b[2]);
		add(ns-b[0]-b[3]);
		add(ns-b[1]-b[2]);
		add(ns-b[1]-b[3]);
		add(ns-b[2]-b[3]);
		sub(ns-b[0]-b[1]-b[2]);
		sub(ns-b[0]-b[1]-b[3]);
		sub(ns-b[0]-b[2]-b[3]);
		sub(ns-b[1]-b[2]-b[3]);
		add(ns-b[0]-b[1]-b[2]-b[3]);
		printf("%lld\n",re);
	}
	return 0;
}
