/*
ID: dxmtb
PROG: 麻烦的聚餐
TIME: 2010.10.12
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=30000;
const int oo=1e8;

int N,re;
int D[MAXN];
int d[MAXN][4];

void solve1()
{
	for(int i=1;i<N;i++)
		for(int j=1;j<=3;j++)
			d[i][j]=oo;
	d[0][3]=d[0][1]=d[0][2]=1;
	d[0][D[0]]=0;
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<=3;j++)
		{
			int w=D[i]!=j;
			d[i][j]=min(d[i][j],d[i-1][j]+w);
			if (j>=2)
				d[i][j]=min(d[i][j],d[i-1][j-1]+w);
			if (j==3)
				d[i][j]=min(d[i][j],d[i-1][1]+w);
		}
	}
	re=min(d[N-1][3],min(d[N-1][1],d[N-1][2]));
}

void solve2()
{
	for(int i=1;i<N;i++)
		for(int j=1;j<=3;j++)
			d[i][j]=oo;
	d[0][3]=d[0][1]=d[0][2]=1;
	d[0][D[0]]=0;
	for(int i=1;i<N;i++)
	{
		for(int j=1;j<=3;j++)
		{
			int w=D[i]!=j;
			d[i][j]=min(d[i][j],d[i-1][j]+w);
			if (j<=2)
				d[i][j]=min(d[i][j],d[i-1][j+1]+w);
			if (j==1)
				d[i][j]=min(d[i][j],d[i-1][3]+w);
		}
	}
	re=min(min(d[N-1][1],min(d[N-1][2],d[N-1][3])),re);
}

int main()
{
	freopen("egroup.in","r",stdin);
	freopen("egroup.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
		scanf("%d",D+i);
	solve1();
	solve2();
	printf("%d\n",re);
	return 0;
}

