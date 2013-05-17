/*
ID: dxmtb
PROG: 核电站问题
TIME: 2010.10.14
STATE: Solved
MEMO: dp
*/
#include <cstdio>
using namespace std;

const int MAXN=55,MAXM=10;

int n,m;
long long d[MAXN][MAXM],re;

int main()
{
	freopen("nucle.in","r",stdin);
	freopen("nucle.out","w",stdout);
	scanf("%d%d",&n,&m);
	d[0][0]=1;
	if (m!=1)
		d[0][1]=1;
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<m;j++)
			d[i][0]+=d[i-1][j];
		for(int j=1;j<m;j++)
			d[i][j]=d[i-1][j-1];
	}
	for(int i=0;i<m;i++)
		re+=d[n-1][i];
	printf("%lld\n",re);
	return 0;
}

