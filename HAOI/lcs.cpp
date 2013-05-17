/*
ID: dxmtb
PROG: HAOI2010 最长公共子序列
TIME: 2011.03.17
STATE: Solved
MEMO: dp
*/
#include <cstdio>
#include <cstring>

const int MAXN=5005;
const int MO=100000000;

char str1[MAXN],str2[MAXN];
int d[2][MAXN],s[2][MAXN];

int main()
{
	freopen("lcs.in","r",stdin);
	freopen("lcs.out","w",stdout);
	scanf("%s",str1);
	scanf(" %s",str2);
	int N=strlen(str1),M=strlen(str2);
	s[0][0]=1;
	if (str1[0]==str2[0])
		d[0][0]=1;
	for(int i=0;i<N;i++)
	{
		int *g=d[i&1],*h=d[(i&1)^1];
		int *p=s[i&1],*q=s[(i&1)^1];
		for(int j=0;j<M;j++)
		if (i || j)
		{
			bool flag=false;
			if (str1[i]==str2[j])
			{
				int nd,ns;
				if (i>=1 && j>=1) nd=h[j-1],ns=q[j-1];
				else nd=0,ns=1;
				if (nd+1>=g[j])
					g[j]=nd+1,p[j]=ns;
			}
			if (i>=1)
			{
				if (h[j]>g[j])
				{
					g[j]=h[j],
					p[j]=q[j];
					flag=true;
				}
				else if (h[j]==g[j])
				{
					p[j]=(p[j]+q[j])%MO;
					flag=true;
				}
			}
			if (j>=1)
			{
				if (g[j-1]>g[j])
					g[j]=g[j-1],
					p[j]=p[j-1];
				else if (g[j-1]==g[j])
				{
					p[j]=(p[j]+p[j-1])%MO;
					if (flag && h[j-1]==g[j])
					{
						p[j]=(p[j]-q[j-1])%MO;
						if (p[j]<0)
							p[j]+=MO;
					}
				}
			}
		}
	       	memset(h,0,sizeof(d[0]));
		memset(q,0,sizeof(s[0]));
	}
	/*
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
			printf("%d ",d[i][j]);
		printf("\n");
	}
		printf("\n");
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
			printf("%d ",s[i][j]);
		printf("\n");
	}*/
	printf("%d\n%d\n",d[(N-1)&1][M-1]-1,s[(N-1)&1][M-1]);
	return 0;
}
