/*
 * Problem: NOI2009 二叉查找树
 * Time: 2011.06.13
 * Author: dxmtb
 * State: Solved
 * Memo: 树形dp
*/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=75;
const int oo=0x7fffffff;

struct Node
{
	int data,w,f;
}node[MAXN];

inline bool operator < (const Node &a,const Node &b)
{
	return a.data<b.data;
}

inline void Min(int &a,int b)
{
	if (b<a)
		a=b;
}

int N,K;
int d[MAXN][MAXN][MAXN],c[MAXN][MAXN][MAXN];
int sum[MAXN];

pair<int,int> tmp[MAXN];
void dp(int i,int j,int p)
{
	if (d[i][j][p]!=oo) return ;
	for(int k=i;k<=j;k++)
		tmp[k].first=node[k].w,tmp[k].second=k;	
	sort(tmp+i,tmp+j+1);
	int rank[MAXN];
	for(int k=i;k<=j;k++)
		rank[tmp[k].second]=k-i+1;
	int p1=0,p2=p;
	for(int k=i;k<=j;k++)
	{
		int cost=sum[j]-sum[i-1];
		int de=d[i][j][p];
		if (rank[k]<=p)
			p2--;
		if (rank[k]<=p+1)
		{
			dp(i,k-1,p1);dp(k+1,j,p2);
			Min(d[i][j][p],d[i][k-1][p1]+d[k+1][j][p2]+cost);
		}
		else
		{
			dp(i,k-1,p1);dp(k+1,j,p2);
			Min(d[i][j][p],d[i][k-1][p1]+d[k+1][j][p2]+cost+K);
			int t1=0,t2=0;
			for(int t=i;t<k;t++)
				if (rank[t]<rank[k])
					t1++;
			for(int t=k+1;t<=j;t++)
				if (rank[t]<rank[k])
					t2++;
			dp(i,k-1,t1);dp(k+1,j,t2);
			Min(d[i][j][p],d[i][k-1][t1]+d[k+1][j][t2]+cost+K*(t1-p1+t2-p2));
		}
		if (rank[k]<=p)
			p1++;
		if (d[i][j][p]!=de)
			c[i][j][p]=k;
	}
}

int main()
{
	freopen("treapmod.in","r",stdin);
	freopen("treapmod.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].data);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].w);
	for(int i=1;i<=N;i++)
		scanf("%d",&node[i].f);
	sort(node+1,node+N+1);
/*	for(int i=1;i<=N;i++)
		printf("%d ",node[i].data);
	printf("\n");
	for(int i=1;i<=N;i++)
		printf("%d ",node[i].w);
	printf("\n");
	for(int i=1;i<=N;i++)
		printf("%d ",node[i].f);
	printf("\n");*/
	for(int i=0;i<=N;i++)
		for(int j=0;j<=N;j++)
			for(int k=0;k<=N;k++)
				d[i][j][k]=oo;
	for(int i=1;i<=N;i++)
	{
		d[i][i][0]=d[i][i][1]=node[i].f;
		d[i][i-1][0]=0;d[i+1][i][0]=0;
		sum[i]=sum[i-1]+node[i].f;
	}	
	dp(1,N,0);
	printf("%d\n",d[1][N][0]);
	return 0;
}
