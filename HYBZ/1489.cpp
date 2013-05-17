/*
 * Problem: 1489: [HNOI2009]双递增序
 * Time: 2011.07.21
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>

const int MAXN=2005;
const int oo=~0u>>1;

inline void Min(int &a,int b)
{
	if (b<a)
		a=b;
}

int N,a[MAXN];
int d[MAXN][MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
			scanf("%d",a+i);
		for(int i=0;i<N;i++)
			for(int j=1;j<=N;j++)
				d[i][j]=oo;
		d[0][1]=-oo;
		for(int i=0;i+1<N;i++)
			for(int j=1;j<=N/2;j++)
				if (d[i][j]!=oo)
				{
					if (a[i]<a[i+1])
						Min(d[i+1][j+1],d[i][j]);
					if (d[i][j]<a[i+1])
						Min(d[i+1][i+2-j],a[i]);
				}
		if (d[N-1][N/2]!=oo)
			printf("Yes!\n");
		else
			printf("No!\n");
	}
	return 0;
}
