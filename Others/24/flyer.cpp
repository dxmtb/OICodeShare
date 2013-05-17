/*
ID: dxmtb
PROG: 线性规划与网络流24题 飞行员配对方案问题
TIME: 2010.3.20
STATE: Solved
MEMO: 二分图匹配
*/
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=101,MAXINT=10000;

int c[MAXN][MAXN],pre[MAXN];

int n1,n2,n;

FILE *fin=fopen("flyer.in","r");
FILE *fout=fopen("flyer.out","w");

int maxflow(int,int);

int main()
{
///////init
	memset(c,0,sizeof(c));
	fscanf(fin,"%d%d",&n1,&n2);
	int n=max(n1,n2);
	while (!feof(fin))
	{
		int x,y;
		fscanf(fin,"%d%d",&x,&y);
		c[x][y]=1;
		c[0][x]=1;
		c[y][n]=1;
	}
/////////
	fprintf(fout,"%d",maxflow(0,n));
	return 0;
}

int maxflow(int s,int t)
{
	int flow=0,n=t;
	while (true)
	{
		memset(pre,-1,sizeof(pre));
		queue <int> q;
		q.push(s);	
		while (!q.empty())
		{
			int now=q.front();
			q.pop();
			for(int i=0;i<=n&&pre[t]<0;i++)
				if (now!=i&&c[now][i]>0&&pre[i]<0)
				{
					q.push(i);
					pre[i]=now;
				}
			if (pre[t]>=0) break;
		}
		if (pre[t]>=0)
		{
			int agu=0x7fffffff;
			for(int m=pre[t],n=t;n!=s;n=m,m=pre[n])
				if (c[m][n]<agu) agu=c[m][n];
			for(int m=pre[t],n=t;n!=s;n=m,m=pre[n])
				c[m][n]-=agu,c[n][m]+=agu;
			flow+=agu;
		}
		else break;
	}
	return flow;
}
