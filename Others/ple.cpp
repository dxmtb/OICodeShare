/*
ID: dxmtb
PROG: 潜水员的问题
TIME: 2010.9.19
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=1000;
const int oo=0x7fffffff/2;

int d[22][80];

int T,A,n;

int main()
{
	freopen("ple.in","r",stdin);
	freopen("ple.out","w",stdout);
	scanf("%d%d",&T,&A);
	for(int i=0;i<=T;i++)
		for(int j=0;j<=A;j++)
			d[i][j]=oo;
	d[0][0]=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int t,a,w;
		scanf("%d%d%d",&t,&a,&w);
		for(int j=T;j>=0;j--)
			for(int k=A;k>=0;k--)
				d[j][k]=min(d[j][k],d[max(j-t,0)][max(k-a,0)]+w);
//		printf("%d\n",d[T][A]);
	}
	printf("%d\n",d[T][A]);
	return 0;
}

