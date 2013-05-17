/*
ID: dxmtb
PROG: 大毒枭
IME: 2010.7.10
STATE: Solved
MEMO: 状态压缩dp
*/
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=16;
const int MAXS=(1<<MAXN)-1;
const int oo=0x7fffffff;

int n;
int d[MAXS+1];
int c[MAXN][MAXN];
int hp[MAXN];

int main()
{
	freopen("kilomanx.in","r",stdin);
	freopen("kilomanx.out","w",stdout);
	scanf("%d\n",&n);
	for(int i=0;i<n;i++)
	{
		char str[MAXN*10];
		fgets(str,MAXN*10,stdin);
		for(int j=0;j<n;j++)
			c[i][j]=str[j]-'0';
	}
	for(int i=0;i<n;i++)
		scanf("%d",hp+i);
	d[0]=0;
	for(int i=1;i<(1<<n);i++)
	{
		d[i]=oo;
		for(int j=0;j<n;j++)
			if (((1<<j)|i)==i)
			{
				int p=i^(1<<j);
				int kill=1;
				for(int k=0;k<n;k++)
					if (((1<<k)|p)==p&&c[k][j]>kill)
						kill=c[k][j];
				if (d[p]+ceil(double(hp[j])/kill)<d[i])
					d[i]=d[p]+ceil(double(hp[j])/kill);
			}
//		printf("%d %d\n",i,d[i]);
	}
	printf("%d\n",d[(1<<n)-1]);
	return 0;
}
