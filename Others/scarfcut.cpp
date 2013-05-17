/*
ID: dxmtb
PROG: 围巾裁剪
TIME: 2010.7.5
STATE: Solved
MEMO: 枚举分割+dp
*/
#include <cstdio>
#include <cstring>
using namespace std;

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)>(b)?(b):(a)

const int MAXN=101;
bool g[MAXN][2*MAXN+2];
int f[MAXN][2*MAXN+2],d[MAXN][2*MAXN+2];
int n,m;

int main()
{
	freopen("scarfcut.in","r",stdin);
	freopen("scarfcut.out","w",stdout);
	memset(g,false,sizeof(g));
	scanf("%d%d",&n,&m);
	for(int i=0,x,y;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		g[x][y]=true;
	}
	int re=0;
	for(int k=1;k<n;k++)
	{
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		int t1=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i*2-1;j++)
				if (!g[i][j]) d[i][j]=1;
		for(int i=k-1;i>=1;i--)
			for(int j=1;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1])
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t1=max(t1,d[i][j]);
			}
		for(int i=2;i<=k;i++)
			for(int j=2;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j>=4)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t1=max(t1,d[i][j]);
			}
		int t2=0;
		for(int i=n-1;i>k;i--)
			for(int j=1;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1])
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t2=max(t2,d[i][j]);
			}
		for(int i=k+2;i<=n;i++)
			for(int j=2;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j>=4)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t2=max(t2,d[i][j]);
			}
		if (re<t1*t1+t2*t2)
			re=t1*t1+t2*t2;
	}
	for(int k=1;k<n;k++)///////////////
	{
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		int t1=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i*2-1;j++)
				if (!g[i][j]) d[i][j]=1;
		for(int i=n-1;i>=1;i--)
			for(int j=1;j<=i*2-1&&j<=2*k;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1]&&j+2<=2*k)
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t1=max(t1,d[i][j]);
			}
		for(int i=2;i<=n;i++)
			for(int j=2;j<=i*2-1&&j<=2*k;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j>=4)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t1=max(t1,d[i][j]);
			}
		int t2=0;
		for(int i=n-1;i>=1;i--)
			for(int j=2*k+1;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1])
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t2=max(t2,d[i][j]);
			}
		for(int i=2;i<=n;i++)
			for(int j=2*k+2;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j-2>=2*k)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t2=max(t2,d[i][j]);
			}
		if (re<t1*t1+t2*t2)
			re=t1*t1+t2*t2;
	}
	for(int k=1;k<n;k++)/*//*/
	{
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		int t1=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i*2-1;j++)
				if (!g[i][j]) d[i][j]=1;
		for(int i=n-1;i>=1;i--)
			for(int j=2*k+2;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1]&&j>2*i-1-2*k)
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t1=max(t1,d[i][j]);
			}
		for(int i=2;i<=n;i++)
			for(int j=2*k+2;j<=i*2-1;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j>=4&&j-2>2*k)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t1=max(t1,d[i][j]);
			}
		int t2=0;
		for(int i=n-1;i>=1;i--)
			for(int j=1;j<=i*2-1&&j<=2*k;j+=2)
			{
				if (!g[i][j]&&!g[i+1][j+1]&&j+2<=2*k)
					d[i][j]=min(d[i+1][j],d[i+1][j+2])+1;
				t2=max(t2,d[i][j]);
			}
		for(int i=2;i<=n;i++)
			for(int j=2;j<=i*2-1&&j<=2*k;j+=2)
			{
				if (!g[i][j]&&!g[i-1][j-1]&&j<=i*2-3&&j>=4&&j<=2*k)
					d[i][j]=min(d[i-1][j],d[i-1][j-2])+1;
				t2=max(t2,d[i][j]);
			}
		if (re<t1*t1+t2*t2)
			re=t1*t1+t2*t2;
	}
	printf("%d\n",re);
	return 0;
}
