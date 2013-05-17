/*
ID: dxmtb
PROG: Sue 的小球(sdtsc 2008)
TIME: 2010.12.16
STATE: Solved
MEMO: dp 当前决策影响未来费用
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1005;

struct Node
{
	int x,y,v;
}node[MAXN];

bool operator < (const Node &a,const Node &b)
{
	return a.x<b.x;
}

int N,X0;
int d[2][MAXN][MAXN];
int w[MAXN][MAXN];
int sum[MAXN];

int main()
{
	scanf("%d%d",&N,&X0);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].x);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].y);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].v);
	sort(node+1,node+1+N);
	for(int i=1;i<=N;i++)
		sum[i]=sum[i-1]+node[i].v;
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j++)
			w[i][j]=sum[i-1]+sum[N]-sum[j];
	for(int i=1;i<=N;i++)
		d[0][i][i]=d[1][i][i]=node[i].y-abs(X0-node[i].x)*sum[N];
	for(int k=1;k<=N;k++)
	for(int i=1,j;(j=k+i)<=N;i++)
		{
			d[0][i][j]=max(d[0][i+1][j]-(node[i+1].x-node[i].x)*w[i+1][j],
				       d[1][i+1][j]-(node[j].x-node[i].x)*w[i+1][j])+node[i].y;
			d[1][i][j]=max(d[1][i][j-1]-(node[j].x-node[j-1].x)*w[i][j-1],
				       d[0][i][j-1]-(node[j].x-node[i].x)*w[i][j-1])+node[j].y;
		}
	printf("%.3f\n",max(d[0][1][N],d[1][1][N])/1000.0);
	return 0;
}

