/*
ID: dxmtb
PROG: 砖
TIME: 2010.11.18
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=305;
const int inf=0x7fffffff;

inline void Max(int &a,int b)
{
	if (b>a) a=b;
}

int N,M,K;
int dy[MAXN][MAXN],dn[MAXN][MAXN];
int wy[MAXN][MAXN],wn[MAXN][MAXN],w[MAXN][MAXN];
char c[MAXN][MAXN];

int main()
{
	freopen("gamea.in","r",stdin);
	freopen("gamea.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			scanf("%d %c",w[i]+j,c[i]+j);
	for(int i=1;i<=M;i++)
	{
		for(int j=1;j<=N;j++)
			wn[i][j]=wn[i][j-1]+w[N-j+1][i];
		int j,k,t;
		for(j=1,k=0,t=0;j<=N;j++)
		{
			if (c[N-j+1][i]=='Y')
				k++;
			t+=w[N-j+1][i];
			wy[i][j-k]=t;
			if (c[N-j+1][i]=='Y')
				wn[i][j-k+1]=t;
			else wn[i][j-k]=t;
		}
	}
	for(int i=1;i<=M;i++)
		for(int j=0;j<=K;j++)
			for(int k=0;k<=j&&k<=N;k++)
			{
				Max(dy[i][j],dy[i-1][j-k]+wy[i][k]);
				if (k>0)
					Max(dn[i][j],dy[i-1][j-k]+wn[i][k]);
				if (k<j)
					Max(dn[i][j],dn[i-1][j-k]+wy[i][k]);
			}
	printf("%d\n",dn[M][K]);
	return 0;
}
