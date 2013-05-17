/*
 * Problem: NOI2009 管道取珠
 * Time: 2011.05.18
 * Author: dxmtb
 * State: Solved
 * Memo: dp
*/
#include <cstdio>
#include <cstring>

const int MAXN=505;
const int MO=1024523;

int d[2][MAXN][MAXN];
char str[2][MAXN];
int N,M;

int main()
{
	freopen("ballb.in","r",stdin);
	freopen("ballb.out","w",stdout);
	scanf("%d%d",&N,&M);
	scanf(" %s",str[0]);
	scanf(" %s",str[1]);
	d[0][0][0]=1;
	for(int i=0;i<=N;i++)
	{
		int (*f)[MAXN]=d[i&1],(*g)[MAXN]=d[(i+1)&1];
		memset(g,0,sizeof(d[0]));
		for(int j=0;j<=M;j++)
			for(int k=0,p=i+j,q;k<=i+j;k++,p--)
				if ((q=f[j][k]))
				{
					if (str[0][i]==str[0][k])
						g[j][k+1]=(g[j][k+1]+q)%MO;
					if (str[0][i]==str[1][p])
						g[j][k]=(g[j][k]+q)%MO;
					if (str[1][j]==str[0][k])
						f[j+1][k+1]=(f[j+1][k+1]+q)%MO;
					if (str[1][j]==str[1][p])
						f[j+1][k]=(f[j+1][k]+q)%MO;
				}
	}
	printf("%d\n",d[N&1][M][N]);
	return 0;
}
