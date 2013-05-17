/*
ID: dxmtb
PROG: 贝茜的晨练计划
TIME: 2010.10.9
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=10005,MAXM=505;
const int oo=100000000;

int n,m;
int w[MAXN];
int d[MAXN][MAXM];

int main()
{
	freopen("cowrun.in","r",stdin);
	freopen("cowrun.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",w+i);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			d[i][j]=-oo;
	d[0][0]=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			if (i+1<=n&&j<m)
				if (d[i][j]+w[i]>d[i+1][j+1])
					d[i+1][j+1]=d[i][j]+w[i+1];
			if (i+j<=n&&j!=0)
				if (d[i][j]>d[i+j][0])
					d[i+j][0]=d[i][j];
		}
		if (d[i][0]>d[i+1][0])
			d[i+1][0]=d[i][0];
	}
	printf("%d\n",d[n][0]);
	return 0;
}


