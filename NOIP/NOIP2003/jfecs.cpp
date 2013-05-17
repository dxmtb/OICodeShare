/*
ID: dxmtb
PROG: NOIP2003 ¼Ó·Ö¶þ²æÊ÷
TIME: 2010.5.13
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=32;

unsigned n,a[MAXN+1],K[MAXN][MAXN],d[MAXN][MAXN];

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		d[i][i]=a[i];
	}
	for(int i=1;i<=n;i++)
		d[i][i-1]=1;
	for(int i=1;i<=n;i++)
		d[i+1][i]=1;
}

void dp()
{
	for(int add=1;add<=n-1;add++)
		for(int i=1;i<n;i++)
		{
			int j=i+add;
			if (j>n)break;
			for(int k=i;k<=j;k++)
				if (d[i][k-1]*d[k+1][j]+a[k]>d[i][j])
					d[i][j]=d[i][k-1]*d[k+1][j]+a[k],K[i][j]=k;
		}
}

void prin(int l,int r)
{
	if (l>r)return ;
	if (l==r)
	{
		printf("%d ",l);
		return;
	}
	int k=K[l][r];
	printf("%d ",k);
	prin(l,k-1);
	prin(k+1,r);
}

void print()
{
	printf("%u\n",d[1][n]);
	prin(1,n);
	printf("\n");
}

int main() 
{
	freopen("jfecs.in","r",stdin);
	freopen("jfecs.out","w",stdout);
	init();
	dp();
	print();
	return 0;
}
