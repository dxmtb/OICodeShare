/*
ID: dxmtb
PROG: NOIP2001 数的划分
TIME: 2010.5.2
STATE: Solved
MEMO: 动态规划 背包
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=200,MAXM=6;

int n,m;
long long d[MAXN+1][MAXM+1];

void init()
{
	scanf("%d%d",&n,&m);
}

int main() 
{
	freopen("sdhf.in","r",stdin);
	freopen("sdhf.out","w",stdout);
	init();
	d[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=1;k<=m;k++)
				d[j][k]+=d[j-i][k-1];
	printf("%d",d[n][m]);
	return 0;
}
