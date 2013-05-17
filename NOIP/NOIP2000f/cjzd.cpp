/*
ID: dxmtb
PROG: NOIP2000 乘积最大
TIME: 2010.5.1
STATE: Solved
MEMO: 动态规划
*/
#include <cstdio>
#include <string>
using namespace std;

const int MAXN=50,MAXK=10;

long long n,m,d[MAXN][MAXK+1],num[MAXN],sum[MAXN][MAXN];

void init()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;num[i++]-='0')
		do{scanf("%c",&num[i]);}while (!(num[i]>='0'&&num[i]<='9'));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=i;k<=j;k++)sum[i][j]=sum[i][j]*10+num[k];	
}

int main() 
{
	freopen("cjzd.in","r",stdin);
	freopen("cjzd.out","w",stdout);	
	init();
	for(int i=0;i<n;i++)
		d[i][0]=sum[0][i];
	for(int i=0;i<n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<i;k++)
				d[i][j]=max(d[i][j],d[k][j-1]*sum[k+1][i]);
	printf("%lld",d[n-1][m]);
    return 0;
}
