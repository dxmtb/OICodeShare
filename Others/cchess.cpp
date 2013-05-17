/*
ID: dxmtb
PROG: 中国象棋
TIME: 2011.03.09
STATE: Solved
MEMO: dp
*/
#include <cstdio>

typedef long long s64;

const int MAXN=105;
const int MO=9999973;

s64 d[MAXN][MAXN][MAXN];
int N,M;

inline void Add(s64 &a,const s64 b)
{
	a=(a+b)%MO;
}

int main()
{
	freopen("cchess.in","r",stdin);
	freopen("cchess.out","w",stdout);
	scanf("%d%d",&N,&M);
	d[0][0][0]=1;
	for(int i=0;i<N;i++)
		for(int j=0;j<=M;j++)
			for(int k=0;k+j<=M;k++)
				if (d[i][j][k])
				{
					const s64 &now=d[i][j][k];
					Add(d[i+1][j][k],now);//-1 -1
					if (k+j+1<=M)
						Add(d[i+1][j+1][k],now*(M-j-k));//0 -1
					if (j>=1)
						Add(d[i+1][j-1][k+1],now*j);//1 -1
					if (k+j+2<=M)
						Add(d[i+1][j+2][k],now*(M-j-k)*(M-j-k-1)/2);//0 0
					if (j>=2)
						Add(d[i+1][j-2][k+2],now*j*(j-1)/2);//1 1
					if (k+j+1<=M)
						Add(d[i+1][j][k+1],now*j*(M-j-k));//0 1
				}
	s64 re=0;
	for(int j=0;j<=M;j++)
		for(int k=0;k+j<=M;k++)
			Add(re,d[N][j][k]);
	printf("%lld\n",re);
	return 0;
}
