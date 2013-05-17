/*
ID: dxmtb
PROG: 棋盘分割
TIME: 2010.9.17
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=9;
const int MAXM=16;
const int oo=0x7fffffff;

int n,m,a[MAXN][MAXN];
double s[MAXN][MAXN];
double d[MAXN][MAXN][MAXN][MAXN][MAXM];
double total;

inline int sqr(int x){return x*x;}

int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	scanf("%d",&m);
	n=8;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",a[i]+j);
			total+=a[i][j];
		}
	total=sqr(total);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			s[i][j]=a[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int a=i;a<=n;a++)
				for(int b=j;b<=n;b++)
					d[i][j][a][b][0]=sqr(s[a][b]-s[i-1][b]-s[a][j-1]+s[i-1][j-1]);
	for(int g=1;g<m;g++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int a=i;a<=n;a++)
					for(int b=j;b<=n;b++)
					{
						double &p=d[i][j][a][b][g];
						p=1e18;
						for(int k=i+1;k<=a;k++)
							for(int q=0;q<g;q++)
								p=min(p,d[i][j][k-1][b][g-1-q]+d[k][j][a][b][q]);
						for(int k=j+1;k<=b;k++)
							for(int q=0;q<g;q++)
								p=min(p,d[i][j][a][k-1][q]+d[i][k][a][b][g-1-q]);
						//if (p==0)cerr<<i<<j<<a<<b<<g<<"wrong\n";
					}
	printf("%.3lf",sqrt(d[1][1][n][n][m-1]/m-total/(m*m)));
	return 0;
}



