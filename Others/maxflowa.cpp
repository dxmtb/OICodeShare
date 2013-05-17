#include <cstdio>
#include <queue>
using namespace std;

const int MAXN=100;

int c[MAXN][MAXN],pre[MAXN];

int n;

FILE *fin=fopen("maxflowa.in","r");
FILE *fout=fopen("maxflowa.out","w");

int maxflow(int,int);

int main()
{
///////init
	memset(c,0,sizeof(c));
	fscanf(fin,"%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			fscanf(fin,"%d",&c[i][j]);
/////////
	fprintf(fout,"%d",maxflow(0,n-1));
	return 0;
}

int maxflow(int s,int t)
{
	int flow=0;
	while (true)
	{
		memset(pre,-1,sizeof(pre));
		queue <int> q;
		q.push(s);	
		while (!q.empty())
		{
			int now=q.front();
			q.pop();
			for(int i=0;i<n&&pre[t]<0;i++)
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
