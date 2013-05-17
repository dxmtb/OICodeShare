/*
ID: dxmtb
PROG: 罪犯问题B
TIME: 2010.10.20
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=1005,MAXM=50005;
const int oo=100000000;

int w[MAXN],d[2][MAXM];
int a1[MAXN],a2[MAXN];
int N,M,K;

int main()
{
	freopen("criminalb.in","r",stdin);
	freopen("criminalb.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",w+i);
	for(int i=0;i<M;i++)
	{
		int X;
		scanf("%d",&X);
		if (X>0) a1[X]++;
		else a2[-X]++;
	}
	for(int i=1;i<=N;i++)
	{
		int *f=d[i&1],*g=d[1-(i&1)];
		for(int j=K;j>=0;j--)
		{
			f[j]=-oo;
			if (j>=a1[i]) f[j]=g[j-a1[i]];
			if (j>=a2[i]) f[j]=max(f[j],g[j-a2[i]]+w[i]);
		}
	}
	printf("%d\n",d[N&1][K]);
	for(int i=0;i<=K;i++)
		d[1][i]=d[0][i]=oo;
	d[0][0]=0;
	for(int i=1;i<=N;i++)
	{
		int *f=d[i&1],*g=d[1-(i&1)];
		for(int j=K;j>=0;j--)
		{
			f[j]=oo;
			if (j>=a1[i]) f[j]=g[j-a1[i]];
			if (j>=a2[i]) f[j]=min(f[j],g[j-a2[i]]+w[i]);
		}
	}
	int re2=oo;
	for(int i=0;i<=K;i++)
		re2=min(re2,d[N&1][i]);
	printf("%d\n",re2);
	return 0;
}
