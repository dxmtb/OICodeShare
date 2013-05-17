/*
ID: dxmtb
PROG: NOI1995 石子归并
TIME: 2010.9.17
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=300;
const int oo=200000000;

int n;
int d[MAXN][MAXN];
int a[MAXN],s[MAXN];

int main()
{
	freopen("shizi.in","r",stdin);
	freopen("shizi.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i];
	for(int i=1;i<n;i++)
		for(int j=1;j<=2*n;j++)
			d[i][j]=oo;
	for(int i=1;i<n;i++)
		for(int j=1;i+j<=n;j++)
			for(int k=0;k<i;k++)
				d[i][j]=min(d[i][j],d[k][j]+d[i-k-1][j+k+1]+s[i+j]-s[j-1]);
	printf("%d\n",d[n-1][1]);
	return 0;
}
