/*
ID: dxmtb
PROG: NOIP2008 传纸条
TIME: 2010.8.21
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=50;

int n,m;
int a[MAXN][MAXN];
int d[MAXN*2][MAXN][MAXN];

void max(int &a,int b)
{
	if (b>a)a=b;
}

int main()
{
	freopen("message.in","r",stdin);
	freopen("message.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			scanf("%d",a[i]+j);
	for(int i=1;i<n+m-1;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<m;k++)
			if (i>=j&&i>=k&&(i==n+m-2||j!=k))
			{
				int sum=a[j][i-j]+a[k][i-k];
				if (i==1||j!=k)max(d[i][j][k],d[i-1][j][k]+sum);
				if (j>=1&&(i==1||j!=k+1))max(d[i][j][k],d[i-1][j-1][k]+sum);
				if (k>=1&&(i==1||j!=k-1))max(d[i][j][k],d[i-1][j][k-1]+sum);
				if (j>=1&&k>=1&&(i==1||j!=k))max(d[i][j][k],d[i-1][j-1][k-1]+sum);
			}
	printf("%d\n",d[n+m-2][m-1][m-1]);
	return 0;
}

