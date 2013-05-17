/*
ID: dxmtb1
PROG: job
LANG: C++
*/
#include <cstdio>
using namespace std;

const int MAXN=1000,MAXM=30;

int N,m1,m2;
int A[MAXM],B[MAXM];
int delay[2][MAXM];
int cost[2][MAXN];

int main()
{
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	scanf("%d%d%d",&N,&m1,&m2);
//	printf("%d\n",N);
	for(int i=0;i<m1;i++)
		scanf("%d",A+i);
	for(int i=0;i<m2;i++)
		scanf("%d",B+i);
	for(int i=0;i<N;i++)
	{
		int mina=delay[0][0]+A[0],na=0;
		for(int j=1;j<m1;j++)
			if (delay[0][j]+A[j]<mina)
				mina=delay[0][j]+A[j],
				na=j;
		delay[0][na]+=A[na];
		cost[0][i]=mina;
	}
	for(int i=0;i<N;i++)
	{
		int minb=delay[1][0]+B[0],nb=0;
		for(int j=1;j<m2;j++)
			if (delay[1][j]+B[j]<minb)
				minb=delay[1][j]+B[j],
				nb=j;
		delay[1][nb]+=B[nb];
		cost[1][i]=minb;
	}
	int re=0;
	printf("%d ",cost[0][N-1]);
	for(int i=0;i<N;i++)
		if (cost[0][i]+cost[1][N-i-1]>re)
			re=cost[0][i]+cost[1][N-i-1];
	printf("%d\n",re);
//	for(int i=0;i<N;i++)
//		printf("%d ",cost[0][i]);
//	for(int i=0;i<N;i++)
//		printf("%d ",cost[1][i]);
	return 0;
}

