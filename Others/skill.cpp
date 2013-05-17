/*
ID: dxmtb
PROG: ¼¼ÄÜÊ÷
TIME: 2010.11.16
STATE: Solved
MEMO: dp
*/
#include <cstdio>
const int MAXN=55,MAXM=505;
const int oo=0x7fffffff;

inline int max(int a,int b){return a>b?a:b;}

int a[MAXN][MAXN];
int d[MAXN][MAXN][MAXM],re;
int n,m;
int sum[MAXN][MAXN];
int main()
{
	freopen("skill.in","r",stdin);
	freopen("skill.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n-i+1;j++)
		{
			scanf("%d",a[i]+j);
			sum[j][i]=sum[j][i-1]+a[i][j];
		}
	for(int i=n;i>=0;i--)
		for(int j=0;j<=n-i+1;j++)
		{
			for(int k=0;k<j;k++)
				d[i][j][k]=-oo;
			for(int k=j;k<=m;k++)
			{
				d[i][j][k]=-oo;
				for(int p=max(0,j-1);p<=n-(i+1)+1;p++)
					d[i][j][k]=max(d[i][j][k],d[i+1][p][k-j]+sum[i][j]);
				if (d[i][j][k]>re)
				{
					re=d[i][j][k];
		//			printf("%d %d %d %d\n",i,j,k,re);
				} 
			}
		}
	printf("%d\n",re);
	return 0;
}
