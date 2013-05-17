/*
ID: dxmtb
PROG: NOI2007 社交网络
TIME: 2011.03.01
STATE: Solved
MEMO: 最短路
*/
#include <cstdio>

const int MAXN=105;
const int oo=1e8;

int d[MAXN][MAXN];
double s[MAXN][MAXN];

int main()
{
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	int N,M;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			d[i][j]=oo,s[i][j]=0;
	for(int i=1;i<=N;i++)
		d[i][i]=0,s[i][i]=1;
	while(M--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		d[a][b]=d[b][a]=c;
		s[a][b]=s[b][a]=1;
	}
	for(int k=1,t;k<=N;k++)
		for(int i=1;i<=N;i++)
		if (i!=k)
			for(int j=1;j<=N;j++)
			if (j!=k && j!=i)
				if ((t=d[i][k]+d[k][j])<d[i][j])
				{
					d[i][j]=d[i][k]+d[k][j];
					s[i][j]=s[i][k]*s[k][j];
				}
				else if (t==d[i][j])
					s[i][j]+=s[i][k]*s[k][j];
	for(int k=1;k<=N;k++)
	{
		double re=0;
		for(int i=1;i<=N;i++)
		if (i!=k)
			for(int j=1;j<=N;j++)
			if (k!=j && i!=j)
			{
				if (d[i][j]==d[i][k]+d[k][j])
					re+=s[i][k]*s[k][j]/double(s[i][j]);
			}
		printf("%.3lf\n",re);
	}		
	return 0;
}
