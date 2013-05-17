/*
ID: dxmtb1
PROG: rockers
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=21;

int d[MAXN][MAXN][MAXN];
int len[MAXN];
int N,T,M;

inline int max(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	freopen("rockers.in","r",stdin);
	freopen("rockers.out","w",stdout);
	scanf("%d%d%d",&N,&T,&M);
	for(int i=1;i<=N;i++)
		scanf("%d",len+i);
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			for(int k=0;k<=T;k++)
			{
				d[i][j][k]=d[i-1][j][T];
				d[i][j][k]=max(d[i][j][k],d[i][j-1][k]);
				if (k>=len[j])
					d[i][j][k]=max(d[i][j][k],
							d[i][j-1][k-len[j]]+1);
			}
	printf("%d\n",d[M][N][T]);
	return 0;
}



