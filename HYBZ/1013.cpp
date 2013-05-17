/*
 * Problem: [JSOI2008]球形空间产生器sphere
 * Time: 2011.05.12
 * Author: dxmtb
 * State: Solved
 * Memo: 高斯消元
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=15;

void swapar(double *a,double *b,int size)
{
	for(int i=0;i<size;i++)
		swap(a[i],b[i]);
}

int N;
double a[MAXN+1][MAXN+1];
double ans[MAXN];

void solve()
{
	for(int i=0;i<N;i++)
	{
		int t=i;
		double ma=a[i][i];
		for(int j=i+1;j<N;j++)
			if (a[j][i]>ma)
				t=j,ma=a[j][i];
		if (t!=i)
			swapar(a[t],a[i],N+1);
		for(int j=i+1;j<N;j++)
		{
			double mul=a[j][i]/a[i][i];
			for(int k=i;k<=N;k++)
				a[j][k]-=a[i][k]*mul;
		}
	}
	for(int i=N-1;i>=0;i--)
	{
		ans[i]=-a[i][N]/a[i][i];
		for(int j=i-1;j>=0;j--)
		{
			double mul=a[j][i]/a[i][i];
			a[j][i]-=a[i][i]*mul;
			a[j][N]-=a[i][N]*mul;
		}
	}
}

double c[MAXN+1][MAXN];
int main()
{
	freopen("1013.in","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N+1;i++)
		for(int j=0;j<N;j++)
			scanf("%lf",c[i]+j);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j]=-2*c[i][j]+2*c[i+1][j];
			a[i][N]+=c[i][j]*c[i][j]-c[i+1][j]*c[i+1][j];
		}
	}
	solve();
	printf("%.3lf",ans[0]);
	for(int i=1;i<N;i++)
		printf(" %.3lf",ans[i]);
	printf("\n");
	return 0;
}
